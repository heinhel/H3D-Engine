#include "../../H3D/XML/XML.hpp"
////////////////////////////////////////////////////////////////
// XML Tree Implementation
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace xml {
		Tree::Tree() {}
		Tree::~Tree() {}

		Node& Tree::getBaseNode() {
			return m_baseNode;
		}
	}
}
/////////////////////////////////////////////////////////////////