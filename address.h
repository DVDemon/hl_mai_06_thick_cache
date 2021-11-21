#ifndef _IGNITE_EXAMPLES_ADDRESS
#define _IGNITE_EXAMPLES_ADDRESS

#include <ignite/binary/binary.h>

struct Address
{
    Address() : street(), zip(0)
    {
        // No-op.
    }

    Address(const std::string &street, int zip) : street(street), zip(zip)
    {
        // No-op.
    }

    std::string ToString()
    {
        std::ostringstream oss;

        oss << "Address [street=" << street << ", zip=" << zip << "]";

        return oss.str();
    }

    std::string street;
    int zip;
};

template <>
struct ignite::binary::BinaryType<Address> : ignite::binary::BinaryTypeDefaultAll<Address>
{
    static void GetTypeName(std::string &dst)
    {
        dst = "Address";
    }

    static void Write(BinaryWriter &writer, const Address &obj)
    {
        writer.WriteString("street", obj.street);
        writer.WriteInt32("zip", obj.zip);
    }

    static void Read(BinaryReader &reader, Address &dst)
    {
        dst.street = reader.ReadString("street");
        dst.zip = reader.ReadInt32("zip");
    }
};

#endif