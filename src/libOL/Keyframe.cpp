// Copyright (c) 2014 Andrew Toulouse.
// Distributed under the MIT License.

#include "Keyframe.h"

#include <fstream>

namespace libol {
    Keyframe Keyframe::decode(std::ifstream& ifs) {
        Keyframe frame;
        frame.header = KeyframeHeader::decode(ifs);
        while(PlayerSegment::probe(ifs))
            frame.players.push_back(PlayerSegment::decode(ifs));
        return frame;
    }
}
