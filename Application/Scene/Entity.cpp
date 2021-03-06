#include "Entity.h"

namespace Nome::Scene
{

DEFINE_META_OBJECT(CEntity) { }

CEntity::CEntity()
{
    if (Name.empty())
    {
        static unsigned int nameCounter = 1;
        Name = "entity" + std::to_string(nameCounter++);
    }
}

CEntity::~CEntity()
{
    for (const auto& comp : Components)
    {
        comp->OnBeforeDetach();
    }
}

std::string CEntity::GetNameWithoutPrefix() const
{

    const auto& fullName = GetName();
    size_t lastDot = fullName.find_last_of('.');
    if (lastDot == std::string::npos)
        return fullName;
    return fullName.substr(lastDot + 1);
}

AST::ACommand* CEntity::SyncToAST(AST::CASTContext& ctx, bool createNewNode)
{
    ctx;
    createNewNode;
    throw "unimplemented";
    return nullptr;
}

bool CEntity::AttachComponent(std::shared_ptr<CComponent> component)
{
    // Make sure the componet is not already attached
    if (component->IsAttached())
        return false;
    component->EntityAttachedTo = this;
    auto& ref = Components.emplace_back(std::move(component));
    ref->OnAttach();
    return true;
}

}
