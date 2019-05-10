
#include <iostream>
#include <sstream>
#include "../esl/esl_json.h"
#include "speech/common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <vector>
#include <map>

using namespace std;

struct tts_config
{
  char api_key[40];       // ��д��ҳ�������appkey �� $apiKey="g8eBUMSokVB1BHGmgxxxxxx"
  char secret_key[40];    // ��д��ҳ�������APP SECRET �� $secretKey="94dc99566550d87f8fa8ece112xxxxx"
  char text[512 * 3 + 1]; // ��Ҫ�ϳɵ��ı�  ���512������
  int text_len;           // �ı��ĳ���
  char cuid[20];
  int spd;
  int pit;
  int vol;
  int per;
  int aue;
  char format[4];
};

class codeHelper
{
private:
  //���캯��˽�л�
  codeHelper()
  {
  }
  static codeHelper *m_pInstance;
  class CGarbo //����Ψһ��������������������ɾ��CSingleton��ʵ��
  {
  public:
    ~CGarbo()
    {
      if (codeHelper::m_pInstance)
        delete codeHelper::m_pInstance;
    }
  };

  unsigned char ToHex(unsigned char x);
  unsigned char FromHex(unsigned char x);
  string notYinghao(const char *str);
  string createRequestEntity(const string &phone, const string &status, const string &type, const string &content, const string &id, const string &recordId);
  string createMosRequestEntity(const string &phone,
                                const string &batchName,
                                const string &bizType,
                                const string &type,
                                const string &content);

  string createSimnetBody(const string &text1, const string &text2);

  RETURN_CODE fill_config(struct tts_config *config, const char *txt);

  RETURN_CODE run_tts(struct tts_config *config, const char *token, const char *fileName);
  int UTF2Uni(const char *src, std::wstring &t);
  std::string ws2s(const std::wstring &ws);


  int  UnicodeToUTF_8(unsigned long * InPutStr, int InPutStrLen,  char *OutPutStr);




  /**
 * ���Ի�ȡaccess_token�ĺ�����ʹ��ʱ��Ҫ���ڰٶ��ƿ���̨������Ӧ���ܵ�Ӧ�ã���ö�Ӧ��API Key��Secret Key
 * @param access_token ��ȡ�õ���access token�����ú���ʱ�贫��ò���
 * @param AK Ӧ�õ�API key
 * @param SK Ӧ�õ�Secret key
 * @return ����0�����ȡaccess token�ɹ�����������ֵ�����ȡʧ��
 */
  int get_access_token(std::string &access_token, const std::string &AK, const std::string &SK);

  static CGarbo Garbo; //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������
public:
  static codeHelper *GetInstance(); //��ȡʵ��
  std::string UrlDecode(const std::string &str);
  string emsCallbackRequest(const string &phone, const string &state,
                            const string &type, const string &content, const string &recordId, const string &order_id);
  string mosCallbackRequest(const string &phone,
                            const string &batchName,
                            const string &bizType,
                            const string &type,
                            const string &content);
string sentiment_classifyRequesst(const string &text);
  RETURN_CODE run(const char *fileName, const char *txt);
  char *simnet(const char *text1, const char *text2);

  string getXmlInput(const string &xmlStr);
  void getKeyWord(multimap<int, string> &keyWord, const string &word);
  void split(const string &s, vector<string> &sv, const char flag = ' ');
string getAliAsrTxt(const string& json);
};
