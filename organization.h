#ifndef _IGNITE_EXAMPLES_ORGANIZATION
#define _IGNITE_EXAMPLES_ORGANIZATION

#include <ignite/binary/binary.h>

#include "address.h"

struct Organization
{
    Organization() : name(), addr()
    {
        // No-op.
    }

    Organization(const std::string &name) : name(name), addr()
    {
        // No-op.
    }

    Organization(const std::string &name, Address addr) : name(name), addr(addr)
    {
        // No-op.
    }

    std::string ToString()
    {
        std::ostringstream oss;

        oss << "Organization [name=" << name << ", Address=" << addr.ToString() << "]";

        return oss.str();
    }

    std::string name;
    Address addr;
};

template <>
struct ignite::binary::BinaryType<Organization> : ignite::binary::BinaryTypeDefaultAll<Organization>
{
    static void GetTypeName(std::string &dst)
    {
        dst = "Organization";
    }

    static void Write(BinaryWriter &writer, const Organization &obj)
    {
        writer.WriteString("name", obj.name);
        writer.WriteObject<Address>("addr", obj.addr);
    }

    static void Read(BinaryReader &reader, Organization &dst)
    {
        dst.name = reader.ReadString("name");
        dst.addr = reader.ReadObject<Address>("addr");
    }
};

#endif