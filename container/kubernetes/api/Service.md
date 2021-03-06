# Service

Load balancing:

- Service
- Ingress Controller
- Service Load Balancer
- Custom Load Balancer

# Service Type

- ClusterIP

A ClusterIP service makes it accessible from any of the Kubernetes cluster's
nodes. The use of virtual IP address for this purpose makes it possible to have
several pods expose the same port on the same node - All of these pods will be
accessible via a unique IP address.

- NodePort

For a NodePort servie, Kubernetes allocates a port from a configured range
(default is 30000-32767), and each node forwards that port, which is the same on
each node, to the service. It is possible to define a specific port number, but
you should take care to avoid potential port conflicts.

Visually
========

```text
        client
           \^
            \\
             \\
              v\
  node 1 <--- node 2
   |^    SNAT
   ||    --->
   v|
 endpoint
```

(1) Client sends packet to node2:nodePort
(2) node2 replaces the source IP address (SNAT) in the packet with its own IP address
(3) node2 replaces the destination IP on the packet with the pod IP
(4) packet is routed to node 1, and then to the endpoint
(5) the pod's reply is routed back to node2
(6) the pod's reply is sent back to the client

Visually (externalTrafficPolicy:Local)
======================================

```text
            client
            ^/   \
           //     \
          /v       X
       node 1     node 2
         ^|
         ||
         |v
      endpoint
```

(1) client sends packet to node2:nodePort, which doesn't have any endpoints
(2) packet is dropped
(3) client sends packet to node1:nodePort, which does have endpoints
(4) node1 routes packet to endpoint with the correct source IP

- LoadBalancer

For a LoadBalancer service, Kubernetes provisions an external load balancer. The
type of service depends on how the specific Kubernetes cluster is configured.

Visually
========

```text
                     client
                       |
                     lb VIP
                     /^
                    v/
 health check ---> node 1    node 2 <--- health check
         200  <---  ^|              --->  500
                    |v
                 endpoint
```

- ExternalIP

An ExternalIP service uses an IP address from the predefined pool of external IP
address to the cluster's nodes. These external IP are not managed by Kubernetes;
they are responsibility of the cluster administrator.

- ExternalName

ExternalName is a special case of service that does not have selectors. It does
not define any ports or endpoints. Instead, it returns the name of an external
service that resides outside the cluster. Such a service works in the same way
as others, with the only difference being that the redirection happens at the
DNS level without proxying or forwarding. Later, you may decide to replace an
external service with an internal one. In this case, you will need to replace a
service definition in your application.

```text
                                             @
                                             |
                                             | https:443
                                 +--------------------------+
                                 |      Frontend Service    |
                                 | app=webapp role=frontend |
                                 +--------------------------+
                                             |
                                             |
           +---------------------------------+----------------------------+
           |                                 |                            |
  +--------------------------+ +--------------------------+ +--------------------------+
  |      Frontend v1 Pod     | |      Frontend v1 Pod     | |     Frontend v2 Pod      |
  | app=webapp role=frontend | | app=webapp role=frontend | | app=webapp role=frontend |
  | version=1.0.0            | | version=1.0.0            | | version=2.0.0            |
  +--------------------------+ +--------------------------+ +--------------------------+
```


# kube-proxy

```text
                                                   +--------+
                                                   | Client |
      +------+                                     +--------+
      | User |                                          |
      +------+                              +--------+-----+---------+
          | create service                  |        | VIP |         |
          |                                 |        +-----+         |
  +----------------+                        |         Service        |
  | kube-apiserver |                        | label selecter: app=wb |
  +----------------+                        +------------------------+
    watch |                                              |
     +------------+            update            +---------------+
     | kube-proxy |----------------------------->| iptables/ipvs |
     +------------+                              +---------------+
                                                  /      |      \
                                                 /       |       \
                                                /        |        \
                                               /         |         \
                                        +-------+    +-------+  +-------+
                                        |  Pod  |    |  Pod  |  |  Pod  |
                                        |app=web|    |app=web|  |app=web|
                                        +-------+    +-------+  +-------+
```
