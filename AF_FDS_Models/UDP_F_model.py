from sklearn.metrics import classification_report
import pandas as pd
from sklearn import tree
from sklearn .tree import DecisionTreeClassifier
import matplotlib.pyplot as plt
from sklearn.metrics import recall_score, precision_score, f1_score, confusion_matrix, accuracy_score, plot_confusion_matrix
from sklearn.metrics import confusion_matrix
import numpy as np
import matplotlib as mpl
from sklearn import ensemble
from sklearn import metrics
from sklearn.metrics import confusion_matrix
import matplotlib.pyplot as plt
import matplotlib as mpl
from sklearn.tree import DecisionTreeClassifier
import csv

trainFile="Trainset_256_bit15_thre100.csv"
testFile= "202006101400.pcap.Mixed_rseed-2222.pcap.bit_15.thre_100.ratio_256.IP.csv"
out256="256 output UDP_F.csv"
metricfile=''


def write_metrics(metricfile,metrics_list):
    with open(metricfile, 'a', newline='') as student_file:
        writer = csv.writer(student_file)
        writer.writerow(metrics_list)


def detect(trainfile,testfile,filename,alg):
    data = pd.read_csv(trainfile,index_col=False)
    data_train =data[data['Label_UDP_2'] == 1]
    train_y = data_train[['Label_UDP_Multi']]
    train_x = data_train[['F_Len_Avg', 'B_Len_Avg']]
    data_test=pd.read_csv(testfile,index_col=False)
    df_test=data_test[data_test['Prelabel_UDP_2'] == 1]
    test_y = df_test[['Label_UDP_Multi']]
    test_x = df_test[['F_Len_Avg', 'B_Len_Avg']]

    if alg=='DT':
        clf = DecisionTreeClassifier(criterion="entropy",random_state=96)
    elif alg=='RF':
        clf= ensemble.RandomForestClassifier(n_estimators=10)

    clf = clf.fit(train_x, train_y)
    y_predict = clf.predict(test_x)
    df_test['Prelabel_UDP_Multi'] = y_predict
    df_test.to_csv(filename, index=None)

    metricfile = testfile + '_Metrics_UDP-F.csv'
    metrics_list=[]
    metrics_list.append(testfile)
    precision = precision_score(test_y, y_predict, average='weighted')
    recall = recall_score(test_y, y_predict,average='weighted')
    F1 = f1_score(test_y, y_predict,average='weighted')

    metrics_list.append(str(precision))
    metrics_list.append(str(recall))
    metrics_list.append(str(F1))
    print(metrics_list)
    print('recall:' + str(recall))
    print('precision: ' + str(precision))
    print('F1 score: ' + str(F1))
    write_metrics(metricfile, metrics_list)

    plt.figure(figsize=(15, 8))
    confusion = confusion_matrix(test_y, y_predict)
    plt.imshow(confusion, cmap=plt.cm.Greens)
    indices = range(len(confusion))
    classes=['Normal','DNS','NTP','SNMP','TFTP','UDP','NETBIOS','MSSQL','CLDAP']
    plt.colorbar()
    plt.title('model: '+alg+'     F1-score: '+str(F1))
    plt.xticks(indices, classes)
    plt.yticks(indices, classes)

    print(metrics.classification_report(test_y, y_predict))
    for first_index in range(len(confusion)):
        for second_index in range(len(confusion[first_index])):
            plt.text(first_index, second_index, confusion[second_index][first_index])
    plt.xlabel('y_pred')
    plt.ylabel('y_true')
    plt.savefig(alg+' 256 UDP_F confusion.pdf')

def dtct():
    detect(trainFile,testFile,out256,'DT')
    # detect(trainFile, testFile, out256, 'RF')

if __name__=='__main__':
    dtct()




