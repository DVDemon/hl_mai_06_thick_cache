#include <iostream>
#include <string>

#include <ignite/ignite.h>
#include <ignite/ignition.h>

#include "organization.h"

using namespace ignite;
using namespace cache;

void PutGet(Cache<int, Organization>& cache) 
{
    // Create new Organization to store in cache.
    Organization org("Microsoft", Address("1096 Eddy Street, San Francisco, CA", 94109));

    // Put organization to cache.
    cache.Put(1, org);

    // Get recently created employee as a strongly-typed fully de-serialized instance.
    Organization orgFromCache = cache.Get(1);

    std::cout <<  ">>> Retrieved organization instance from cache: " << std::endl;
    std::cout << orgFromCache.ToString() << std::endl;
    std::cout << std::endl;
}

void PutGetAll(Cache<int, Organization>& cache) 
{
    // Create new Organizations to store in cache.
    Organization org1("Microsoft", Address("1096 Eddy Street, San Francisco, CA", 94109));
    Organization org2("Red Cross", Address("184 Fidler Drive, San Antonio, TX", 78205));

    // Put created data entries to cache.
    std::map<int, Organization> vals;

    vals[1] = org1;
    vals[2] = org2;

    cache.PutAll(vals);

    // Get recently created organizations as a strongly-typed fully de-serialized instances.
    std::set<int> keys;

    keys.insert(1);
    keys.insert(2);

    std::map<int, Organization> valsFromCache = cache.GetAll(keys);

    std::cout <<  ">>> Retrieved organization instances from cache: " << std::endl;
        for (std::map<int, Organization>::iterator it = valsFromCache.begin(); it != valsFromCache.end(); ++it) 
        std::cout <<  it->second.ToString() << std::endl;

    std::cout << std::endl;
}

auto main() -> int {
    IgniteConfiguration cfg;

    cfg.igniteHome = "/home/stud/ignite/apache-ignite-2.11.0-bin";
    //cfg.springCfgPath ="/home/stud/ignite/apache-ignite-2.11.0-bin/examples/config/example-cache.xml";
    //cfg.springCfgPath = "/home/stud/src/hl_mai_06_thick_cache/config/example-cache.xml";

    try
    {
        // Start a node.
        Ignite grid = Ignition::Start(cfg);

        std::cout << std::endl;
        std::cout << ">>> Cache put-get example started." << std::endl;
        std::cout << std::endl;

        // Get cache instance.

        Cache<int, Organization> cache = grid.GetOrCreateCache<int, Organization>("atomic");

        // Clear cache.
        cache.Clear();

        PutGet(cache);
        PutGetAll(cache);

        // Stop node.
        Ignition::StopAll(false);
    }
    catch (IgniteError& err)
    {
        std::cout << "An error occurred: " << err.GetText() << std::endl;

        return err.GetCode();
    }

    std::cout << std::endl;

    return 1;
}