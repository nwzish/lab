#include<iostream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"

using namespace std;
using namespace ns3;

int main (int argc, char *argv[]){
  CommandLine cmd;
  cmd.Parse (argc, argv);

  Time::SetResolution (Time::NS);
  
  NodeContainer nodes;
  nodes.Create (4);

  PointToPointHelper ptp1;

  ptp1.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  ptp1.SetChannelAttribute ("Delay", StringValue ("2ms"));



  NetDeviceContainer d1,d2,d3,d4;
  d1 = ptp1.Install (nodes.Get(0),nodes.Get(1));
  d2 = ptp1.Install (nodes.Get(1),nodes.Get(2));
  d3 = ptp1.Install (nodes.Get(2),nodes.Get(3));
  d4 = ptp1.Install (nodes.Get(3),nodes.Get(0));


  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;

  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i1 = address.Assign (d1);

  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer i2 = address.Assign (d2);

  Ipv4InterfaceContainer i3 = address.Assign (d3);
  address.SetBase ("10.1.3.0", "255.255.255.0");

  Ipv4InterfaceContainer i4 = address.Assign (d4);
  address.SetBase ("10.1.4.0", "255.255.255.0");

  Ipv4GlobalRoutingHelper::PopulateRoutingTables();

  uint16_t port1=9;
  uint16_t port2=12;


  UdpEchoServerHelper s1(port1);
  UdpEchoServerHelper s2(port2);

  ApplicationContainer serverApps;
  s1.Install (nodes.Get (0));
  s2.Install (nodes.Get (3));

  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper c1 (i2.GetAddress (1), port1);

  UdpEchoClientHelper c2 (i3.GetAddress(0), port2);


  c1.SetAttribute ("MaxPackets", UintegerValue (5));
  c1.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  c1.SetAttribute ("PacketSize", UintegerValue (1024));

  c2.SetAttribute ("MaxPackets", UintegerValue (5));
  c2.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  c2.SetAttribute ("PacketSize", UintegerValue (1024));


  ApplicationContainer clientApps1,clientApps2;
  clientApps1 = c1.Install (nodes.Get (0));
  clientApps1.Start (Seconds (2.0));
  clientApps1.Stop (Seconds (10.0));

  clientApps2 = c2.Install (nodes.Get (3));
  clientApps2.Start (Seconds (2.0));
  clientApps2.Stop (Seconds (10.0));


  AnimationInterface anim("ring.xml");
  anim.SetConstantPosition(nodes.Get(0),100,100);
  anim.SetConstantPosition(nodes.Get(1),200,100);
  anim.SetConstantPosition(nodes.Get(2),100,100);
  anim.SetConstantPosition(nodes.Get(0),200,200);

//  anim.EnablePacketMetaData();


  Simulator::Run ();
  Simulator::Destroy ();
  cout<<"simulation done\n";
  return 0;
}
