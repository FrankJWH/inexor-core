#include "inexor/flowgraph/functions/playsound/fl_playsound.hpp"

namespace inexor {
namespace vscript {

    // TODO: implement playsound correctly
    CFunctionPlaysoundNode::CFunctionPlaysoundNode(const vec position, const const char* id)
    {
        pos = position;
        sound_id = atoi(id);
    }

    CFunctionPlaysoundNode::~CFunctionPlaysoundNode()
    {
    }


    void CFunctionPlaysoundNode::in()
    {
        playsound(sound_id);
        last_time = SDL_GetTicks();
        out();
    }

    bool CFunctionPlaysoundNode::OnLinkAsChildNodeAttempt(const CScriptNode* parent)
    {
        return false;
    }

    bool CFunctionPlaysoundNode::OnLinkAsParentNodeAttempt(const CScriptNode* child)
    {
        return false;
    }

};
};
