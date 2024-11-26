#include "RabMessageBuffer.h"

#include <algorithm>

namespace argos {

  /****************************************/
  /****************************************/

  RabMessageBuffer::RabMessageBuffer() {
    m_unCurrentTime = 0;
  }

  /****************************************/
  /****************************************/

  RabMessageBuffer::~RabMessageBuffer() {}

  /****************************************/
  /****************************************/

  void RabMessageBuffer::SetTimeLife(const UInt32& un_max_time_to_live) {
    m_unMaxTimeToLive = un_max_time_to_live;
  }

  /****************************************/
  /****************************************/

  void RabMessageBuffer::Update() {
    // create a function which returns true if the message is too old and shall be removed
    auto IsOld = [this](auto e){ return e.second < m_unCurrentTime - m_unMaxTimeToLive; };

    // iterate all the messages to find the too old ones to remove
    auto end = std::remove_if(m_vecBufferElements.begin(), m_vecBufferElements.end(), IsOld);

    // remove the too old messages from the vector
    m_vecBufferElements.erase(end, m_vecBufferElements.end());

    // increment the passed time
    m_unCurrentTime += 1;
  }

  /****************************************/
	/****************************************/

  void RabMessageBuffer::AddMessage(CCI_EPuckRangeAndBearingSensor::SReceivedPacket* c_packet) {
    m_vecBufferElements.push_back(std::make_pair(*c_packet, m_unCurrentTime));
  }

  /****************************************/
  /****************************************/

  std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> RabMessageBuffer::GetMessages(){
    std::vector<CCI_EPuckRangeAndBearingSensor::SReceivedPacket*> vecRabMessages;
    std::transform(
      m_vecBufferElements.begin(), m_vecBufferElements.end(),
      std::back_inserter(vecRabMessages),
      [](auto& o){ return &(o.first); }
    );
    return vecRabMessages;
  }

  /****************************************/
  /****************************************/

  void RabMessageBuffer::Reset() {
    m_vecBufferElements.clear();
    m_unCurrentTime = 0;
  }
}
