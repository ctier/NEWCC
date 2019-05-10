//2019-5-7
#pragma once
//IVRҵ�������
#include<stdio.h>
#include<string>
#include "common/structdef.h"
#include "esl/esl.h"
#include <map>
using namespace std;
//ת�˹��Ļ����ڵ�
#define IVR_AGENT_node -1
//ת�˹�������ڵ���flow�ϵ�index
#define IVR_AGENT_FLOW_INDEX 9999
#define IVR_AGNET_MSG "TransformAgent"
//��ͨ�����ⰴ��
#define IVR_ANS_DFTM  "-1"
typedef struct 
{
	t_ivrnode* current;		//��ǰ�ڵ���Ϣ
	map<string,t_ivrnode*>next; //��һ���ڵ�ͼ dmtf---ivrnode
}t_flownode;

enum CustomerLevel
{
	IVR_normail,
	IVR_VIP
};
enum SessionState
{
	IVR_Session_call,
	IVR_Session_Destory, //�Ự�Ѿ�������
};
typedef struct ivrsession
{
public:
	ivrsession():m_customtype(IVR_normail),m_startTimestamp(time(NULL)),m_sessionState(IVR_Session_call)
	{

	}
	int m_companyid;
	int m_currentnodeid;
	int m_dmtf;
	string m_uuid;
	int m_customtype;
	int m_startTimestamp;
	esl_handle_t *m_handle;
	int m_sessionState;				//����Ựͨ��״̬
	friend bool operator < (ivrsession a,ivrsession b)
	{
		if(a.m_customtype<b.m_customtype)
			return false;
		if(a.m_startTimestamp < b.m_startTimestamp)
			return false;
		return true;
	}
	//string m_
}ivrsession;
class Managerivr
{
public:
	Managerivr(){}
	~Managerivr(){}
	static void Init();
	static Managerivr*Instance();
	static void Initivrflow(vector<t_ivrnode>&nodetable);
	t_ivrnode* Getnodeinfo(int companyid,int currentnode,string dtmfnum);
	static map<int,map<int,t_ivrnode> > m_IVRnodetable; //conpanyid--nodeid--nodeinfo
	static map<string,t_flownode> m_flowtable;  //companyid_nodeid:flownode

};