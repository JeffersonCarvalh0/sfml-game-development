# ifndef RESOURCE_HOLDER_INL
# define RESOURCE_HOLDER_INL

# include <utility>
# include <stdexcept>

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
const std::string &filename) {
    Resource resource;
    if (!resource.loadFromFile(filename))
        throw(std::runtime_error("ResourceHolder::load - Failed to load " + filename));

    resourceMap.insert({ id, std::move(resource) });
}

template<typename Resource, typename Identifier>
template<typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
const std::string &filename, const Parameter &secondParam) {
    Resource resource;
    if (!resource.loadFromFile(filename, secondParam))
        throw(std::runtime_error("ResourceHolder::load - Failed to load " + filename));

    resourceMap.insert({ id, std::move(resource) });
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    return resourceMap.find(id)->second;
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    return resourceMap.find(id)->second;
}

# endif /* end of include guard: RESOURCE_HOLDER_INL */
