# Kubernetes Cluster

## Kubernetes coordinates a highly available cluster of computers that are connected to work as a single unit

The abstractions in Kubernetes allow you to deploy containerized applications to
a cluster without tying them specifically to individual machines. To make use of
this new model of deployment, applications need to be packaged in a way that
decouples them from individual hosts: they need to be containerized.
Containerized applications are more flexible and available than in past
deployment models, where applications were installed directly onto specific
machines as packages deeply integrated into the host.

## Kubernetes automates the distribution and scheduling of application containers across a cluster in a more efficient way

A Kubernetes cluster consists of two types of resources:

- The =Master= coordinates the cluster
- =Node= are the workers that run applications

Cluster Diagram

![Cluster Diagram](img/module_01_cluster.svg)

The Master is responsible for managing the cluster. The master coordinates all
activities in your cluster, such as scheduling applications, maintaining
applications' desired state, scaling applications, and rolling out new updates.

A node is a VM or a physical computer that serves as a worker machine in a
Kubernetes cluster. Each node has a Kubelet, which is an agent for managing the
node and communicating with the Kubernetes master. The node should also have
tools for handling container operations, such as =Docker= or =rkt=. A Kubernetes
cluster that handles production traffic should have a minimum of three nodes.

When you deploy applications on Kubernetes, you tell the master to start the
application containers. The master schedules the containers to run on the
cluster's nodes. The nodes communicate with the master using the Kubernetes API,
which the master exposes. End users can also use the Kubernetes API directly to
interact with the cluster.

## Scaling

Scaling is accomplished by changing the number of replicas in a Deployment.

Before:

![Scaling Before](img/module_05_scaling1.svg)

After:

![Scaling After](img/module_05_scaling2.svg)

## Rolling update

### Stage 1:

![Rolling Update Stage 1](img/module_06_rollingupdates1.svg)

### Stage 2:

![Rolling Update Stage 2](img/module_06_rollingupdates2.svg)

### Stage 3:

![Rolling Update Stage 3](img/module_06_rollingupdates3.svg)

### Stage 4:

![Rolling Update Stage 4](img/module_06_rollingupdates4.svg)
