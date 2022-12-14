from sklearn.metrics import classification_report
import pandas as pd
from sklearn.metrics import recall_score, precision_score, f1_score
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
from sklearn import ensemble
from sklearn.tree import DecisionTreeClassifier
import csv

trainFile="Trainset_256_bit15_thre100.csv"
testFile= "202006101400.pcap.Mixed_rseed-2222.pcap.bit_15.thre_100.ratio_256.IP.csv"
metricfile=''
def writeprelabel(filename,prelabel):
    df = pd.read_csv(filename)
    df['Prelabel_UDP_2'] = prelabel
    df.to_csv(filename, index=None)

def write_metrics(metricfile,metrics_list):
    with open(metricfile, 'a', newline='') as student_file:
        writer = csv.writer(student_file)
        writer.writerow(metrics_list)


def detect(trainfile,testfile,alg):
    data = pd.read_csv(trainfile)
    train_y = data[['Label_UDP_2']]
    train_x = data[['F_Pck', 'B_Pck', 'F_Hash_IPT', 'B_Hash_IPT', 'F_Pck_Spd', 'B_Pck_Spd']]
    data_test=pd.read_csv(testfile)
    test_y = data_test[['Label_UDP_2']]
    # test_x = data_test[['protocol','F_Pck','B_Pck','B_Hash_IP','B_Hash_port','F_TCP_S','B_TCP_S']]
    test_x = data_test[['F_Pck', 'B_Pck', 'F_Hash_IPT', 'B_Hash_IPT', 'F_Pck_Spd', 'B_Pck_Spd']]

    if alg=='DT':
        clf = DecisionTreeClassifier(criterion='entropy',max_depth=10,min_samples_leaf=1,random_state=None,splitter='best') #,random_state=99
        print('alg: DT')
    elif alg=='RF':
        clf= ensemble.RandomForestClassifier(n_estimators=10)
        print('alg: RF')

    clf = clf.fit(train_x, train_y)
    y_predict = clf.predict(test_x)
    writeprelabel(testfile, y_predict)

    metrics_list = []
    metricfile = testfile + '_Metrics_UDP-C.csv'
    metrics_list.append(testfile)
    precision = precision_score(test_y, y_predict)
    recall = recall_score(test_y, y_predict)
    F1 = f1_score(test_y, y_predict)

    metrics_list.append(str(precision))
    metrics_list.append(str(recall))
    metrics_list.append(str(F1))

    print('recall:' + str(recall))
    print('precision: ' + str(precision))
    print('F1 score: ' + str(F1))
    write_metrics(metricfile, metrics_list)
    plt.figure(figsize=(15, 8))
    t = classification_report(test_y, y_predict, target_names=['0','1'])
    classes=['Normal','UDP-based flood']
    confusion = confusion_matrix(test_y, y_predict)
    plt.imshow(confusion, cmap=plt.cm.Greens)
    indices = range(len(confusion))
    plt.xticks(indices, classes,fontsize=16)
    plt.yticks(indices, classes,fontsize=16)
    plt.colorbar()
    plt.title('model: '+alg+'     F1-score: '+str(F1))
    plt.rcParams.update({'font.size': 16})
    plt.xlabel('y_pred',fontsize=16)
    plt.ylabel('y_true',fontsize=16)

    # show the data and Fig
    for first_index in range(len(confusion)):
        for second_index in range(len(confusion[first_index])):
            plt.text(first_index, second_index, confusion[second_index][first_index])
    # plt.show()
    plt.savefig(alg+' 256 UDP_C confusion.pdf')

def dtct():
    detect(trainFile, testFile, 'DT')
    # detect(trainFile, testFile, 'RF')

if __name__=='__main__':
    dtct()





