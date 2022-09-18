# AF_FDS

AF_FDS is a project proposed for detecting DDoS attacks. Its main function is: after sampling the traffic (optional), record and extract the traffic features using the data structure DCSS(Double Composite Structure Sketch) proposed in the paper. Based on the traffic features extracted by DCSS,  machine learning models can be trained to detect DDoS attacks. The use of DCSS and machine learning code is described below. *AF_FDS_DCSS* is the feature extraction program for DCSS, and *AF_FDS_Models* is the machine learning program. In addition, we also provide test methods to monitor network traffic in real-time.

### *1. AF_FDS_DCSS*

##### **1.1 Description**

We provide the code of AF_FDS_DCSS with the following functions: (1)split the attack data in CIC DDoS 2019, (2)mix pcap data, (3)analyze local pcap files, and (4) capture and analyze traffic in real-time.

DCSS (Double Composite Structure Sketch) is a data structure customized for detecting DDoS attacks and can be viewed as a two-dimensional array of buckets with *d* rows and *w* columns. Each bucket of DCSS consists of a combination of counters and hash tables. Each counter/hash table records a statistical feature of the traffic. When the statistics recorded by the bucket reach a specific threshold, the values in the bucket are extracted as a feature vector. Therefore, DCSS can record and extract multiple features of network traffic simultaneously.

##### **1.2 Usage**

- **tools.split_sequ_pcap**

**Use: Split the attack data in CIC DDoS 2019**

URL of the CIC DDoS 2019 dataset: https://www.unb.ca/cic/datasets/ddos-2019.html

The CIC DDoS 2019 attack data contains 2 days of captured data, we use the data from one of the days for the training set and the data from the other day for the test set. To extract the different attack data from the data, we need to use this program. The attack data uses sequential file naming rules, we read the data according to the attack time and then extract the attack data.

**step1:** Modify the settings of  **tools.split_sequ_pcap.exe** in data.cfg;

```
SSPF_first_pcap = "G:/2020data/UIB/day2/PCAP-03-11/SAT-03-11-2018_0";  
SSPF_type = 0;          //split type 0-- by time（s）， 1--by packet number.
SSPF_begin = 5739;
SSPF_end = 6252;
SSPF_payload = 0;       //0 -- no payload， 1-- keep original payload.
```
The meanings of the parameters are as follows:

- SSPF_first_pcap: The name of the first file name,  and the other files are also placed in the same path.
- SSPF_type: Split type. 0: split by time(s), 1: split by packet number.
- SSPF_begin: The start time/packet number of the segment.
- SSPF_end: The end time/packet number of the segment.
- SSPF_payload: Whether the packet contains payload. 0:no payload, 1:keep original payload. Since the packet of the MAWI data to be mixed does not contain payload, the data generated here also does not contain payload.    

|Date|Interception time|Attack type|
| ---- | ---- | ---- |
|SAT-01-12-2018|7539 sec - 8128 sec|LDAP|
|SAT-01-12-2018|8415 sec - 9000 sec|MSSQL|
|SAT-01-12-2018|9225 sec - 9813 sec|NETBIOS|
|SAT-01-12-2018|13076 sec - 13660 sec|UDP|
|SAT-01-12-2018|15161 sec - 15452 sec|SYN|
|SAT-03-11-2018|2600 sec - 3069 sec|NETBIOS|
|SAT-03-11-2018|3827 sec - 4297 sec|LDAP|
|SAT-03-11-2018|4560 sec - 5082 sec|MSSQL|
|SAT-03-11-2018|5739 sec - 6252 sec|UDP|
|SAT-03-11-2018|7871 sec - 8341 sec|SYN|

Operating environment: 

Windows or Linux system

Compiling environment:

* Windows: vscode + mingw 10.2.0 + cmake 

* Ubuntu: vscode + gcc 9.3.0 + cmake+ libpcap

**step2:** Run the program. The compiled program and the files needed to run the program are under the **bin** path.



- **tools.mix_pcap**

**Use: Mix pcap data**

**step1:** Modify the settings of **tools.mix_pcap.exe** in data.cfg;

URL of the MAWI dataset: [MAWI-20200603](http://mawi.wide.ad.jp/mawi/samplepoint-F/2020/202006031400.html), [MAWI-20200610](http://mawi.wide.ad.jp/mawi/samplepoint-F/2020/202006101400.html) 
We also download two MAWI data at the same time: MAWI-20200603, MAWI-20200610, which are mixed with the attack data. One data is used for training and the other data is used for testing.
The program is used to mix the MAWI data with the attack data. We calculate an insertion time for each DDoS traffic to align time. We first define the flow duration in the MAWI traffic as *D*, and the flow duration in the DDoS traffic as *d*. If *D**>**d*, the new initial time is randomly generated in the interval of (0, *D**−**d*). If *D**≤**d*, the new initial time is randomly generated in the interval of (0, *α**∗**D*). The symbol *α* is a mixing coefficient, which should be as small as possible so that most of the packets in the DDoS traffic can be mixed into the MAWI traffic when *D* is not large enough. After adding the new initial time to the original offset in MAWI traffic, we can obtain the insertion time of DDoS traffic.

```
MP_main_file = "h:/2022data/traffic/public/202004081615.pcap";      
MP_mixed_files_path = "h:/2022data/traffic/";                       
MP_start_time = -1;                  // -1--automatic positioning，>=0--positioning time
MP_payload = 0;                      // payload  0--no，1--yes
MP_random_seed = 2022;
```
The meanings of the parameters are as follows:

- MP_main_file: The path of the main file.
- MP_mixed_files_path: The path of the mixed files,the main file is mixed with all the files under this path.
- MP_start_time:  -1:automatic positioning，≥0:positioning time.
- MP_payload: Whether the packet contains payload. 0:no payload, 1:keep original payload.
- MP_random_seed: Random seed. Used to randomly select the starting point.

Operating environment:

Windows or Linux system

Compiling environment:

* Windows: vscode + mingw 10.2.0 + cmake 

* Ubuntu: vscode + gcc 9.3.0 + cmake+ libpcap

**step2:** Run the program. The compiled program and the files needed to run the program are under the **bin** path.



- **DCSS_pcap**

**Use: Analyze local pcap file**

**step1:** Modify the seetings of **DCSS pcap** in data.cfg;

```
DCSS_in_pcap_file = "/home/cayman/data/pcap/202006031400.pcap.cut_type0_0-20_payload0.pcap";
//DCSS_in_pcap_file = "G:/2020data/public/20200603/202006031400.pcap.Mixed_rseed-2022.pcap";
DCSS_random_seed = 2022; 
```

The meanings of the parameters are as follows:

- DCSS_in_pcap_file: The path of the pcap file to be analyzed.
- DCSS_random_seed: Random seed. Used to randomly select the starting point of packet sampling.

**step2**: Modify the settings of **DCSS sketch sets** in data.cfg;

```
//ratio
DCSS_ratio = 1; //ratio 0(1/1),1(1/8),2(1/16),3(1/32),4(1/64),5(1/128),6(1/256),7(1/512),8(1/1024),9(1/2048),10(1/4096),11(1/8192),12(1/16384),13(),14(1/65536)
//key type
//flowkey---2
DCSS_key_type = 2;                      
//feature
/*
statistics feature
a --- forward Pck. (1B)
b --- backward Pck.(1B)
c --- forward length range (count+1)B
d --- backward length range (count+1)B
e --- forward IP+port hash16 distribution (2B)
f --- backward IP+port hash16 distribution (2B)
l --- forward Average packet length (2B)
m --- backward Average packet length (2B)
p --- forward packet speed
q --- backward packet speed
2 --- (TCP) forward SYN (1B)
3 --- (TCP) backward SYN (1B)
*/
DCSS_sketch_feature = "abcdeflmpq23";       

DCSS_sketch_range_count = 1;
DCSS_sketch_range_TCP_1 = 0;
DCSS_sketch_range_UDP_1 = 0;

DCSS_sketch_hash_bit = 25;              
DCSS_sketch_threshold = 100;            
```

The meanings of the parameters are as follows:

- DCSS_ratio: Sampling ratio. The packets are sampled before the features are extracted. 1/8, 1/16, 1/32, and 1/64 are the recommended settings.
- DCSS_key_type: *flowkey*. *flowkey* is the key extracted from each arriving packet. The *flowkey* is used as input to the hash function, and the value output by the hash function is used to locate the buckets that should be updated in DCSS.
- DCSS_sketch_feature: The DCSS bucket composition. The bucket composition selected for detecting DDoS attacks is "abcdeflmpq23".
- DCSS_sketch_range_count: DCSS sketch range count.
- DCSS_sketch_range_TCP_1: DCSS sketch TCP payload range threshold.
- DCSS_sketch_range_UDP_1: DCSS sketch UDP payload range threshold.
- DCSS_sketch_hash_bit: A parameter that is used to pre-allocate memory for DCSS. The number of buckets *w* in each row of DCSS is set to *2^DCSS_sketch_hash_bit*. The number of rows *d* of DCSS is 4 by default.
- DCSS_sketch_threshold: The threshold for extracting feature vectors. A bucket is considered to be saturated when statistics of *DCSS_sketch_threshold* packets are recorded in it. If all the *d* buckets corresponding to a *flowkey* are saturated, the minimum values of the counters and hash tables in the *d* buckets are extracted as a feature vector. After extracting the features, the DCSS bucket is recycled by subtracting the minimum value. *DCSS_sketch_threshold* is set to 100 in the paper.

Operating environment:

Windows or Linux system

Compiling environment:

* Windows: vscode + mingw 10.2.0 + cmake 

* Ubuntu: vscode + gcc 9.3.0 + cmake+ libpcap

**step3:** Run the program. The compiled program and the files needed to run the program are under the **bin** path.



- **DCSS_capture**

**Use: Capture and analyze traffic in real-time**

**step1**: Modify the settings of **DCSS capture** in data.cfg;

```
DCSS_dev = "enp0s31f6";
DCSS_out_pcap_file = "/home/cayman/data/pcap/20220909.pcap";
DCSS_dump_type = 2;             //0 -- not dump, 1 -- only sample, 2 -- all
DCSS_max_packet = 5000000;      
DCSS_capture_time = 900;       
```

The meanings of the parameters are as follows:

* DCSS_dev: The NIC that captures the traffic.

*	DCSS_out_pcap_file: The path and file name to save the captured traffic locally.	

*	DCSS_dump_type: Whether to dump the file locally. 0: no dump; 1: dump only the sampled traffic; 2: dump all traffic.

*	DCSS_max_packet: Set the maximum number of packets to be captured.
*	DCSS_capture_time: Capture time(s).

Operating environment:

Uses libpcap underlay and therefore runs on Linux systems.

Compilation environment:

Ubuntu: vscode + gcc 9.3.0 + cmake+ libpcap

**step2**: Same as **step2** in **DCSS_pcap**.

**step3:** Run the program. The compiled program and the files needed to run the program are under the **bin** path.



### *2. AF_FDS_Models*

##### **2.1 Description**

The above program will output feature vectors to a **.csv file or Redis database, with each feature vector identified by *flowkey*.

The classifiers can be obtained by machine learning after labeling the traffic features extracted by DCSS. We trained three classifiers, namely SYN classifier, UDP-C classifier and UDP-F classifier. The SYN classifier is used for detecting SYN flood, the UDP-C classifier is used for coarse-grained detection of UDP-based flood, and the UDP-F classifier is used for fine-grained detection of UDP-based flood.

##### **2.2 Usage**

*SYN classifier*

- Label the feature files (.csv file) extracted by DCSS as a training set or testing set. 
- Modify *trainFile* and *testFile* in SYN_model.py 
- (Optional) Choose a machine learning algorithm 
- Run the program

*UDP-C classifier* 

- Label the feature files (.csv file) extracted by DCSS as a training set or testing set. 
- Modify *trainFile* and *testFile* in UDP_C_model.py 
- (Optional) Choose a machine learning algorithm 
- Run the program

*UDP-F classifier*

- Label the feature files (.csv file) extracted by DCSS as a training set or testing set. 
- Modify *trainFile* and *testFile* in UDP_F_model.py 
- (Optional) Choose a machine learning algorithm 
- Run the program

Note: The UDP-F classifier must be used after the UDP-C classifier, because the input of UDP-F depends on the output of UDP-C.

**2.3 Test**

A training set file(Trainset_256_bit15_thre100.csv) and a testing set file(202006101400.pcap.Mixed_rseed-2222.pcap.bit_15.thre_100.ratio_256.IP.csv) have been provided to evaluate the classifiers.



### *3. Other test method*

**Test method for real-time monitoring of high-speed network traffic**

The real network environment is simulated by real-world traffic replay in Mininet, and the system topology is shown in Figure 1. Pcap parsing, packet slicing, IP modification, checksum modification, topology reconstruction, and code replay are included in the traffic replay.

- Pcap parsing is responsible for removing useless or unrepresentative link packets and leaving *N* links to obtain the source IP list and destination IP list, after the collected normal traffic and attack traffic packet files are analyzed separately.
- Slicing packets means removing packets whose source or destination IPs are not in the IP list parsed in the first step. Modify the source and destination IPs to Mininet intranet IPs respectively. And modifying the checksum so that the packets can be replayed.
- Generate the corresponding Mininet topology and code for replaying traffic based on the source and destination IP lists. Running the simulated real network environment on each of the two high-performance hosts.
- Replicating the simulated real traffic from the two high-performance hosts to the traffic analysis server after configuring the flow tables.
- The traffic analysis server runs AF_FDS_DCSS to store the extracted traffic features in the Redis database. As a high-speed in-memory database, Redis satisfies real-time, highly concurrent requirements and is suitable for high-speed network traffic feature access.

[![system topology](https://github.com/zlshao/SDS_project/raw/main/images/system.png)](https://github.com/zlshao/SDS_project/blob/main/images/system.png)

 Figure 1 System topology

| Device Name                                                  | Device Configuration                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| Host1 for Replay Traffic Host2 for Replay Traffic Traffic Analysis System | CPU: Inter Core i7-12700K 3.6GHz RAM: 128GB 3200MHz ROM: 5TB NIC1: 10000Mbps NIC2: 1000Mbps |
| TAP Switch                                                   | Centec V580-48X6Q-TAP                                        |

 If you have any problems, please contact [zlshao@seu.edu.cn](mailto:zlshao@seu.edu.cn).

