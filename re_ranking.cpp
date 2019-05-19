/*
    created by: qiaolei
    e-mail:qiaolei000@126.com
    time:2019.05.19 9:00 am
    thank you for watching!
*/

#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

void normalization(const float *tempList)
{
    float square = 0.0;
    float sum = 0.0

    for(unsigned i =0;i<tempList.size();i++)
    {
        square += tempList[i] * tempList;
        sum += tempList[i];
    }
    float sqrt_square = sqrt(square);
    float average = sum / float(tempList.size()) * 1.0;
    for(unsigned j =0;j<tempList.size();j++)
    {
        tempList[j] = (tempList[i] - average) / sqrt_square * 1.0;
    }
}

void original_distance(const float *prode, const vector<vector<float>>& gallery, const float *original_distance,const float *sort_original)
{
    for(unsigned i = 0;i<gallery.size();i++)
    {
        float temp = 0.0;
        for(unsigned j = 0; j < gallery[0].size();j++)
        {
            temp = power((prode[j] - gallery[i][j]),2);
        }
        original_distance[i] = sqrt(temp);
    }

    for(unsigned i = 0; i< original_distance,size();i++){
        sort_original[i] = sort_original[i];
    }
    sort(temp_original.begin(),temp_original.end());
}

int findIndex(float *begin, int &length, float &value)
{
    for(unsigned i = 0;i<length;i++){
        if(!equal(value,begin[i]))
            continue;
        else
        {
            return i;
        } 
    }
}

vector<vector<float>>krnn(const float *prode,  const vector<vector<float>>& gallery, const float *original_distance,const float *sort_original,
                          const int& k1, const int&k2){
        //通过original_dis排序之后的前k1个向量特征
    vector<vector<float>>initRank(k1);
    for(unsigned i = 0;i<k1;i++)
    {
        initRank[i] = gallery[findIndex(original_distance,original_distance.size(),sort_original[i])];
    }

    //双方都在对方的前k1个集合中
    float * temp = new float[original_distance.size() * sizeof(float)];
    float * sort_temp = new float[original_distance.size() * sizeof(float)];
    vector<vector<vector<float>>>initRank_all(k1);
    for(unsigned i = 0;i<k1;i++)
    {
        original_distance(initRank[i],gallery,temp,sort_temp);
        for(unsigned k =0;k<initRank_all.size();k++)
        {
            initRank_all[i][k]=gallery[findIndex(original_distance,original_distance.size(),sort_original[k])]
        }
    }

    //获取交集矩阵
    vector<vetcor<float>>final_rank;
    for(unsigned i =0;i<initRank.size();i++)
    {
        bool exitss = false;
        for(unsigned j =0;j<initRank_all.size();j++)
        {
            if(initRank_all[j].find(initRank[i])){
                exitss = true;
                continue;
            }
            else
            {
                exitss = true;
                break;
            }
        }
        if(exitss){
            final_rank.push_back(initRank[i]);
        }
    }
}

void jaccard_distance(const float *prode,  const vector<vector<float>>& gallery, const float *original_distance,const float *sort_original
                      const float *jaccard_distance,const int &k1, const int &k2)
{
    vector<vector<float>>prode_j_first = krnn(prode,gallery,original_distance,sort_original,k1,k2);
    vector<vector<vector<float>>>gallery_j;
    for(unsigned i = 0;i<gallery.size();i++){
        gallery_j.push_back(krnn(gallery[i],gallery,original_distance,sort_original,k1,k2))
    }

    //更鲁棒的k-rnn集合
    vector<vector<float>>prode_j;
    for(unsigned i = 0;i<gallery.size();i++)
    {
        set_union(prode_j_first.begin(),prode_j_first.jj.end(),gallery_j[i].begin,gallery_j[i].begin()+k2,inserter(prode_j,prode_j.begin()));
    }

    for(unsigned i = 0;i<jaccard_distance.size();i++)
    {
        vector<vector<float>>union;
        vector<vector<float>>intersection;
        set_union(prode_j.begin(),prode_j.end(),gallery_j[i].begin(),gallery_j[i].end(),inserter(union,union.begin()));
        set_intersection(prode_j.begin(),prode_j.end(),gallery_j[i].begin(),gallery_j[i].end(),inserter(intersection,intersection.begin()));
        jaccard_distance[i] = (float)intersection.size() / (float)union.size() * 1.0;
    }
}

void re_renking(float *prode, vector<vector<float>>& gallery, const float *original_distance, const float*jaccard_distance,
                const int &lambda, const int &k1, const int &k2)
{
    //0、输出向量特征归一化
    normalization(prode);
    for(unsigned i = 0;i<gallery.size();i++){
        normalization(gallery[i]);
    }
     
    //1、求解马式距离
    float * sort_original = new float[original_distance.size() * sizeof(float)];
    original_distance(prode,gallery,original_distance,sort_original);


    //2、求解杰卡德距离
    jaccard_distance(prode,gallery,original_distance,temp_original,jaccard_distance,k1,k2);

    //3、两个距离之间的加权和
    for(unsigned i =0;i<reranking_distance.size();i++){
        reranking_distance[i] = lambda * original_distance[i]+ (1 - lambda) * jaccard_distance[i];
    }

    delete temp_original;

}

//入口
int main()
{
    int outDim = 1536; //图片特征向量的维度
    int count = 1000; //假设整个序列的长度
    float *prode = new float[outDim * sizeof(float)]; //给定目标的输出特征，假设已经赋值
    vector<vector<float>(outDim)>(count) gallery; //整个序列模型输出的特征向量，一个二维数组

    //distance
    float *original_distance = new float[count * sizeof(float)];
    float *jaccard_distance = new float[count * sizeof(float)];
    float *reranking_distance = new float[count * sizeof(float)];
    int lambda = 0.3;
    int k1 = 20;
    int k2 = 6;

    re_renking(prode,gallery,original_distance,jaccard_distance,reranking_distance,lambda,k1,k2);
    //reranking_distance为所求

    return 0;
}
