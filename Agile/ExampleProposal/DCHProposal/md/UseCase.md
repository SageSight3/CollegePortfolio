# Issue Policy

### Actor
* Agent

### Description
After an agent inputs a policy's info, the Agent System should pass it to the CRRS and CRAS, as needed, to assess coverage risk and rate. Then, once it receives a rate back from them, the Agent System will pass it back to the agent  and wait for them to greenlight issuing the policy and up front fee. Once the agent gives the Agent System the go ahead, the Agent System will issue the up front and policy, as permitted and defined (See [Issues List](./IssuesList.md)).

### Important Considerations
1. In the future, issuing the up front fee may fall under a generic issue charge use case.

### Conversation

**[convo name]** - Alt: [alt convo name]
**Actor:** Agent
Agent Action | System Response
---|---
Input policy info | .
. | Pass policy info to to CRRS and CRAS as needed/specified
. | Receive rate from respective system
Greenlight up front fee and policy | .
. | Issue up front fee and policy as permitted/defined<sup>1</sup>
1. Later on, this may become part of a generic use case for issuing fees.