# ifndef RESOURCE_HOLDER_HPP
# define RESOURCE_HOLDER_HPP

# include <map>
# include <string>

template<typename Resource, typename Identifier>
class ResourceHolder {
private:
    std::map<Identifier, Resource> resourceMap;

public:
    void load(Identifier id, const std::string &filename);

    template<typename Parameter>
    void load(Identifier id, const std::string &filename, const Parameter &secondParam);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
};

# include "resource_holder.inl"

# endif /* end of include guard: RESOURCE_HOLDER_HPP */
