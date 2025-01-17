/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/

#include "qtzyre.h"

///
//  Copy-construct to return the proper wrapped c types
QZyre::QZyre (zyre_t *self, QObject *qObjParent) : QObject (qObjParent)
{
    this->self = self;
}


///
//  Constructor, creates a new Zyre node. Note that until you start the
//  node it is silent and invisible to other nodes on the network.
//  The node name is provided to other nodes during discovery. If you
//  specify NULL, Zyre generates a randomized node name from the UUID.
QZyre::QZyre (const QString &name, QObject *qObjParent) : QObject (qObjParent)
{
    this->self = zyre_new (name.toUtf8().data());
}

///
//  Destructor, destroys a Zyre node. When you destroy a node, any
//  messages it is sending or receiving will be discarded.
QZyre::~QZyre ()
{
    zyre_destroy (&self);
}

///
//  Return our node UUID string, after successful initialization
const QString QZyre::uuid ()
{
    const QString rv = QString (zyre_uuid (self));
    return rv;
}

///
//  Return our node name, after successful initialization. First 6
//  characters of UUID by default.
const QString QZyre::name ()
{
    const QString rv = QString (zyre_name (self));
    return rv;
}

///
//  Set the public name of this node overriding the default. The name is
//  provide during discovery and come in each ENTER message.
void QZyre::setName (const QString &name)
{
    zyre_set_name (self, name.toUtf8().data());

}

///
//  Set node header; these are provided to other nodes during discovery
//  and come in each ENTER message.
void QZyre::setHeader (const QString &name, const QString &param)
{
    zyre_set_header (self, name.toUtf8().data(), "%s", param.toUtf8().data());

}

///
//  Set verbose mode; this tells the node to log all traffic as well as
//  all major events.
void QZyre::setVerbose ()
{
    zyre_set_verbose (self);

}

///
//  Set UDP beacon discovery port; defaults to 5670, this call overrides
//  that so you can create independent clusters on the same network, for
//  e.g. development vs. production. Has no effect after zyre_start().
void QZyre::setPort (int portNbr)
{
    zyre_set_port (self, portNbr);

}

///
//  Set the TCP port bound by the ROUTER peer-to-peer socket (beacon mode).
//  Defaults to * (the port is randomly assigned by the system).
//  This call overrides this, to bypass some firewall issues when ports are
//  random. Has no effect after zyre_start().
void QZyre::setBeaconPeerPort (int portNbr)
{
    zyre_set_beacon_peer_port (self, portNbr);

}

///
//  Set the peer evasiveness timeout, in milliseconds. Default is 5000.
//  This can be tuned in order to deal with expected network conditions
//  and the response time expected by the application. This is tied to
//  the beacon interval and rate of messages received.
void QZyre::setEvasiveTimeout (int interval)
{
    zyre_set_evasive_timeout (self, interval);

}

///
//  Set the peer silence timeout, in milliseconds. Default is 5000.
//  This can be tuned in order to deal with expected network conditions
//  and the response time expected by the application. This is tied to
//  the beacon interval and rate of messages received.
//  Silence is triggered one second after the timeout if peer has not
//  answered ping and has not sent any message.
//  NB: this is currently redundant with the evasiveness timeout. Both
//  affect the same timeout value.
void QZyre::setSilentTimeout (int interval)
{
    zyre_set_silent_timeout (self, interval);

}

///
//  Set the peer expiration timeout, in milliseconds. Default is 30000.
//  This can be tuned in order to deal with expected network conditions
//  and the response time expected by the application. This is tied to
//  the beacon interval and rate of messages received.
void QZyre::setExpiredTimeout (int interval)
{
    zyre_set_expired_timeout (self, interval);

}

///
//  Set UDP beacon discovery interval, in milliseconds. Default is instant
//  beacon exploration followed by pinging every 1,000 msecs.
void QZyre::setInterval (size_t interval)
{
    zyre_set_interval (self, interval);

}

///
//  Set network interface for UDP beacons. If you do not set this, CZMQ will
//  choose an interface for you. On boxes with several interfaces you should
//  specify which one you want to use, or strange things can happen.
//  The interface may by specified by either the interface name e.g. "eth0" or
//  an IP address associalted with the interface e.g. "192.168.0.1"
void QZyre::setInterface (const QString &value)
{
    zyre_set_interface (self, value.toUtf8().data());

}

///
//  By default, Zyre binds to an ephemeral TCP port and broadcasts the local
//  host name using UDP beaconing. When you call this method, Zyre will use
//  gossip discovery instead of UDP beaconing. You MUST set-up the gossip
//  service separately using zyre_gossip_bind() and _connect(). Note that the
//  endpoint MUST be valid for both bind and connect operations. You can use
//  inproc://, ipc://, or tcp:// transports (for tcp://, use an IP address
//  that is meaningful to remote as well as local nodes). Returns 0 if
//  the bind was successful, else -1.
int QZyre::setEndpoint (const QString &param)
{
    int rv = zyre_set_endpoint (self, "%s", param.toUtf8().data());
    return rv;
}

///
//  This options enables a peer to actively contest for leadership in the
//  given group. If this option is not set the peer will still participate in
//  elections but never gets elected. This ensures that a consent for a leader
//  is reached within a group even though not every peer is contesting for
//  leadership.
void QZyre::setContestInGroup (const QString &group)
{
    zyre_set_contest_in_group (self, group.toUtf8().data());

}

///
//  Set an alternative endpoint value when using GOSSIP ONLY. This is useful
//  if you're advertising an endpoint behind a NAT.
void QZyre::setAdvertisedEndpoint (const QString &value)
{
    zyre_set_advertised_endpoint (self, value.toUtf8().data());

}

///
//  Apply a azcert to a Zyre node.
void QZyre::setZcert (QZcert *zcert)
{
    zyre_set_zcert (self, zcert->self);

}

///
//  Specify the ZAP domain (for use with CURVE).
void QZyre::setZapDomain (const QString &domain)
{
    zyre_set_zap_domain (self, domain.toUtf8().data());

}

///
//  Set-up gossip discovery of other nodes. At least one node in the cluster
//  must bind to a well-known gossip endpoint, so other nodes can connect to
//  it. Note that gossip endpoints are completely distinct from Zyre node
//  endpoints, and should not overlap (they can use the same transport).
void QZyre::gossipBind (const QString &param)
{
    zyre_gossip_bind (self, "%s", param.toUtf8().data());

}

///
//  Set-up gossip discovery of other nodes. A node may connect to multiple
//  other nodes, for redundancy paths. For details of the gossip network
//  design, see the CZMQ zgossip class.
void QZyre::gossipConnect (const QString &param)
{
    zyre_gossip_connect (self, "%s", param.toUtf8().data());

}

///
//  Set-up gossip discovery with CURVE enabled.
void QZyre::gossipConnectCurve (const QString &publicKey, const QString &param)
{
    zyre_gossip_connect_curve (self, publicKey.toUtf8().data(), "%s", param.toUtf8().data());

}

///
//  Unpublish a GOSSIP node from local list, useful in removing nodes from list when they EXIT
void QZyre::gossipUnpublish (const QString &node)
{
    zyre_gossip_unpublish (self, node.toUtf8().data());

}

///
//  Start node, after setting header values. When you start a node it
//  begins discovery and connection. Returns 0 if OK, -1 if it wasn't
//  possible to start the node.
int QZyre::start ()
{
    int rv = zyre_start (self);
    return rv;
}

///
//  Stop node; this signals to other peers that this node will go away.
//  This is polite; however you can also just destroy the node without
//  stopping it.
void QZyre::stop ()
{
    zyre_stop (self);

}

///
//  Join a named group; after joining a group you can send messages to
//  the group and all Zyre nodes in that group will receive them.
int QZyre::join (const QString &group)
{
    int rv = zyre_join (self, group.toUtf8().data());
    return rv;
}

///
//  Leave a group
int QZyre::leave (const QString &group)
{
    int rv = zyre_leave (self, group.toUtf8().data());
    return rv;
}

///
//  Receive next message from network; the message may be a control
//  message (ENTER, EXIT, JOIN, LEAVE) or data (WHISPER, SHOUT).
//  Returns zmsg_t object, or NULL if interrupted
QZmsg * QZyre::recv ()
{
    QZmsg *rv = new QZmsg (zyre_recv (self));
    return rv;
}

///
//  Send message to single peer, specified as a UUID string
//  Destroys message after sending
int QZyre::whisper (const QString &peer, QZmsg *msgP)
{
    int rv = zyre_whisper (self, peer.toUtf8().data(), &msgP->self);
    return rv;
}

///
//  Send message to a named group
//  Destroys message after sending
int QZyre::shout (const QString &group, QZmsg *msgP)
{
    int rv = zyre_shout (self, group.toUtf8().data(), &msgP->self);
    return rv;
}

///
//  Send formatted string to a single peer specified as UUID string
int QZyre::whispers (const QString &peer, const QString &param)
{
    int rv = zyre_whispers (self, peer.toUtf8().data(), "%s", param.toUtf8().data());
    return rv;
}

///
//  Send formatted string to a named group
int QZyre::shouts (const QString &group, const QString &param)
{
    int rv = zyre_shouts (self, group.toUtf8().data(), "%s", param.toUtf8().data());
    return rv;
}

///
//  Return zlist of current peer ids.
QZlist * QZyre::peers ()
{
    QZlist *rv = new QZlist (zyre_peers (self));
    return rv;
}

///
//  Return zhash of current peer names against peer ids.
QZhash * QZyre::peers_identity ()
{
    QZhash *rv = new QZhash (zyre_peers_identity (self));
    return rv;
}

///
//  Return zlist of current peers of this group.
QZlist * QZyre::peersByGroup (const QString &name)
{
    QZlist *rv = new QZlist (zyre_peers_by_group (self, name.toUtf8().data()));
    return rv;
}

///
//  Return zlist of currently joined groups.
QZlist * QZyre::ownGroups ()
{
    QZlist *rv = new QZlist (zyre_own_groups (self));
    return rv;
}

///
//  Return zlist of groups known through connected peers.
QZlist * QZyre::peerGroups ()
{
    QZlist *rv = new QZlist (zyre_peer_groups (self));
    return rv;
}

///
//  Return the endpoint of a connected peer.
//  Returns empty string if peer does not exist.
QString QZyre::peerAddress (const QString &peer)
{
    char *retStr_ = zyre_peer_address (self, peer.toUtf8().data());
    QString rv = QString (retStr_);
    zstr_free (&retStr_);
    return rv;
}

///
//  Return the value of a header of a conected peer.
//  Returns null if peer or key doesn't exits.
QString QZyre::peerHeaderValue (const QString &peer, const QString &name)
{
    char *retStr_ = zyre_peer_header_value (self, peer.toUtf8().data(), name.toUtf8().data());
    QString rv = QString (retStr_);
    zstr_free (&retStr_);
    return rv;
}

///
//  Explicitly connect to a peer
int QZyre::requirePeer (const QString &uuid, const QString &endpoint, const QString &publicKey)
{
    int rv = zyre_require_peer (self, uuid.toUtf8().data(), endpoint.toUtf8().data(), publicKey.toUtf8().data());
    return rv;
}

///
//  Return socket for talking to the Zyre node, for polling
QZsock * QZyre::socket ()
{
    QZsock *rv = new QZsock (zyre_socket (self));
    return rv;
}

///
//  Return underlying ZMQ socket for talking to the Zyre node,
//  for polling with libzmq (base ZMQ library)
void * QZyre::socketZmq ()
{
    void * rv = zyre_socket_zmq (self);
    return rv;
}

///
//  Print zyre node information to stdout
void QZyre::print ()
{
    zyre_print (self);

}

///
//  Return the Zyre version for run-time API detection; returns
//  major * 10000 + minor * 100 + patch, as a single integer.
quint64 QZyre::version ()
{
    uint64_t rv = zyre_version ();
    return rv;
}

///
//  Self test of this class.
void QZyre::test (bool verbose)
{
    zyre_test (verbose);

}
/*
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Read the zproject/README.md for information about making permanent changes. #
################################################################################
*/
