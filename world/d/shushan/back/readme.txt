
        Mudos V22pre11 for WIN95/NT with COM extension

Ŀ¼
��һ��    ϵͳ��鼰���ָ����Ĵ���
�ڶ���    LPC�ϵ���ǿ
������    COM extension�﷨
���Ľ�    LPC��COM extension��ϱ��
��¼һ    V21���mudlibתV22��ʱӦע�������
��¼��    Mudos v22pre11 with COM extension�е�COM����
��¼��    Mudos v22pre11 with COM extension�ļ���


��һ��    ϵͳ��鼰���ָ����Ĵ���

	Mudos V22pre11 for WIN95/NT with COM extension ( ���¼��
pre11 with Com)���廪��ѧ�����ϵ���ľ���������Mudos V22pre11�Ļ�
���Ͽ������ɡ��Ƚ�ԭ�汾��Mudos V22pre11��˵������汾��Mudos����
��һЩ���������˶�COM�����֧�֡�
	COM( Component Object Model )��Microsoft��˾�����һ������
���������������Mudos�м���COM��֧�֣���Ҫ��Ϊ��������һЩ���е�
���켼������Դ���ֲ�Mudos����Ĺ��ܲ��㡣����COM�ľ���˵����ο�OLE
��̵����ϡ�
	
	Mudos V22pre11�Ѿ�������V11��Ĳ��ٴ�����get_host_by_addr��
����ֵ����select�����ĵ��ò����ȵȡ��������߽�pre11��ֲ��WIN32ƽ̨
����ʵ�������з��ֻ����в�������ġ�
    һ���Ƚ����Ե�������random���������⣬WIN32ƽ̨��random������16
λ�ģ����õ����ϵͳ��ʱ�ͻ��з�Χ�������������pre11 with com���Ѷ�
��������иĽ���ʹ����LPC�е�random��32λ�ġ�
    ��һ����explode_string������bug,����ĳЩ����»���������array_t
����Ԫ��û�з�ֵ���������UNIXϵͳ��Ҳ������ʲô���⣬��WIN32������
�ᵼ��Mudos���������߶�������������Բ�������
    ������һЩ�����Ĵ���filesize�����Ե�bug�������϶������޸ġ�
	
    ��������������汾��mudos������ʲô����ʱ��������Ҫԭ��Ļ�����������
�ĵ�ַ��ϵ�����ǻᾡ��������ġ�

    �ƾ� BBS:         wwj  quake
    SMTH BBS:         wwj  KCN
    Internet EMAIL:   wwj@telekbird.com.cn
                      zhoulin@cai.cic.tsinghua.edu.cn



�ڶ���    LPC�ϵ���ǿ

    Mudos V22�汾���V11����ԣ�LPC��������class���ͣ�������һЩ
efunc������һһ˵����

    V22�汾�е�class����������C��struct,LPC�ľ䷨���£�

    class class_name {
	type member_name1;
	type member_name2;
	...
    };
    ע���Աֻ���Ǳ�����

    ����һ��class����ʱ�䷨��

    class class_name object_name;

    ʹ�ö���֮ǰӦ���ȶԶ����ʼ����
	
    object_name = new ( class class_name );

    ������class����ĳ�ԱʱӦ��ʹ�� -> ���š�

    object_name -> member_name1 = 0;

    ������һ��LPC���ӣ�

class npcdata {
    string name;
    int age;
};

class npcdata * data;

int set_npcdata(int id,string n,int a)
{
    if(nullp(data)){
        data=allocate(10);
    }
    data[id]=new(class npcdata);
    data[id]->name=n;
    data[id]->a=n;
}

    ��ʹ��Ч�����������class������һ��array�����ò�ࡣ

    Ϊ֧��class���ͣ������˹ؼ���new��ǰ���Ѿ����˽��ܡ�
����һ��classp��efunc�������ж�һ�������Ƿ�class���͡�

	


������    COM extension�﷨

    Ϊ��֧��COM����pre11 with COM extension��class����������չ��
	
    �������ӵ��Ƕ�class�ĳ�Ա������֧�֣������������֮��class����
�ͺ�C++�еĵ�����Ƚ������ˡ��������һ������Ա������class���ӡ�

class ab
{
     int a;
     int add();
}

int ab::add()        // ab�ĳ�Ա���� add()
{
    return a++;      // ab�ĳ�Ա���� a++
}

class ab b;

useab()
{
    b=new(class ab);
    b->a=0;           // b->a is 0
    b->add();         // then b->a is 1
}
  
    ���ڳ�Ա�����ĳ��֣��б�Ҫ֧���ڳ�Ա�����з��ʱ�class�����������
һ��this�ؼ��֣�������ָʾ��ǰ��class��������int ab::add()�Ϳ���д��
int ab::add()
{
    return this->a++;
}
    ��Ȼthis��Ҫ�������ǽ�class�Լ�������ĺ�����

    ������class��Ա������֧�ֺ���������һ���﷨������COM���󡣸�ʽ����:

class class_name {
    member and member function ...
} = " com_class_id ";

    com_class_id����Ҫ���õ�com�����CLSID����ProgID������Microsoft
IE��HTML Viewer�ؼ���CLSID��
		{EAB22AC3-30C1-11CF-A7EB-0000C05BAE0B}
ProgID�� 
		Microsoft Web Browser Control
    class_name������ʹ�õ�Interface�����֣���HTML Viewer�ؼ���һ���ӿ���   
        IWebBrowser
    class ��member��member function��Ӧ��������ӿڵ����Ժͷ�����ͨ��
VC�д���OLE/COM Viewer���Կ���Microsoft Web Browser Control��IWebBrowser
�Ķ����������ģ����֣�������

[
  uuid(EAB22AC1-30C1-11CF-A7EB-0000C05BAE0B),       // ������Ǹ�CLSID
  helpstring("Web Browser interface"),         
  hidden,
  dual
]

dispinterface IWebBrowser {
    methods:

    [id(0xfffffdda), helpstring("Refresh the currently viewed page.")]
    void Refresh();                                // һ������ 

    [id(0x00000068), helpstring("Navigates to a URL or file.")]
    void Navigate(                                 // ��һ������   
         [in] BSTR URL, 
         [in] VARIANT* Flags, 
         [in] VARIANT* TargetFrameName, 
         [in] VARIANT* PostData, 
         [in] VARIANT* Headers);

    [id(0x000000ce), propget, helpstring("The horizontal position (pixels) of the frame window relative to the screen/container.")]
    long Left();                 
	// ��Ȼд��methods�������progget���ԣ�ʵ���ϻ�����Ϊ�����ԣ�
	// ���Ƕ�����ֵ�ķ���

    [id(0x000000ce), propput, helpstring("The horizontal position (pixels) of the frame window relative to the screen/container.")]
    void Left([in] long rhs);    
	// ��Ȼд��methods�������progput���ԣ�ʵ���ϻ�����Ϊ�����ԣ�
	// ����д����ֵ�ķ���

	// �ȵȡ�����
}

    ���LPC�п����õ�class�͸ö���ɣ�

class IWebBrowser {
    void Refresh();
    int Left;
} = "{EAB22AC1-30C1-11CF-A7EB-0000C05BAE0B}"; 
    ����ַ���������дΪ Microsoft Web Browser Control
	
    ��������������壬���׼��C++������ûʲô��Ĳ�𡣳�ԱRefresh
������������MIDL�Ķ���ûʲô�仯��Left���Ե����ͱ����int��Navigate
����û�ӽ�����������Ϊ��LPC��COM������ת��ʱ�����������͵Ĳ�����������
�ġ�

    Ŀǰ��pre11 with COM extension֧����������ת����

    LPC�� int     �� COM�� int,long ����ת����
    LPC�� string  �� COM�� BSTR     ����ת����
    LPC�� float   �� COM�� float    ����ת����
    LPC�� void    �� COM�� void     ����ת����
    LPC�� array   ת��   COM�� IDispatch * ��
    LPC�� class   ת��   COM�� IDispatch * ��
    LPC�� object  ת��   COM�� IDispatch * ��
    LPC�� mapping ת��   COM�� IDispatch * ��

    ����"����ת��"����˼��֧�ָ�������Ϊ�������Դ��ݣ�Ҳ������Ϊ����ֵ����
���Ե����͡�
    "ת��"����ζ�ŵ���ģ�ֻ����Ϊ������

    �����޷�ת���ķ��������ԣ���Ҫд��class�Ķ����С�

    ʹ��COM�����class����ͨ��class��ͬ������ʹ������IWebBrowser�����ӣ�

int UseIt()
{
    class IWebBrowser web;
    web=new (class IWebBrowser);
    web.Left=10;
    web.Refresh();
}

    ����ʹ��IWebBrowser��Ŀ����˵�����ʹ��COM������ʵ��IWebBrowser
������Mudos��ʹ��(Mudos��һ��telnet���������ò���һ�������)��



���Ľ�    LPC��COM extension��ϱ��

    pre11 with COM extension�����ṩ�˼���COM��������������ĳ���ͨѶ��
���嶨���뿴��¼�������Ժ��˵�����ҽ����ᵽ IMudos,IMValue,IMNumber,
IMString,IMReal,IMClass,IMObject,IMArray,IMMapping,IMProgram,
IMFunction�⼸���ӿڡ�

    ��һ�ڽ�������LPC���������COM�������潫����һ�������VC5�б�дLPC
���õ�COM����

    ������ý���һ��ATL com dll�Ĺ��̣�Ȼ��������һ��ATL Class�������
���classȡ��ΪCTestʱ�������õ��Ľӿ�(Interface)���ͳ���ITest��Ȼ����
�Ϳ��������Interface��������Ժͷ�����

    ע��������ӵ���������ֻ����
	    int,BSTR,float
    ������ӵķ�����������ֻ����
	    int,BSTR,float
    ��������ֻ����
	    int,BSTR,float,IDispatch *
    ��int,BSTR,float�Ĵ����һ���COMһ�¡���IDispatch *�Ĵ���Ӧ�ý���
����IMValue����Ȼ�����IMValue��Type()��GetExtend()ȡ����Ӧ���͵Ķ���
    ����LPC�ж����class��Ա����

    int Test(int i,class CTest c);

    ��Ӧ��COM�����Ա�����͸��ǣ�
    MIDL  interface:  
        HRESULT Test([in] int i,[in] IDispatch *p,[out,retval] int *pVal);
    MIDL  dispinterface:
        int Test([in] int i,[in] IDispatch *p);
    C++:
        STDMETHOD(Test)(int i,IDispatch *p,int *pVal);
    ��Test��ʵ��ʱӦ���������ģ�

STDMETHODIMP CTest::Test(int i,IDispatch *p,int *pVal)
{
    // ��Щ�ӿڵĺ�����鿴���ɵ�mudos.h
    if(!pVal)return S_FALSE;
    IMValue v(p);
    if(v.GetType()!=VP_CLASS)return S_FALSE;  
    IMClass c(v.GetExtend());

    // now use i,c
    // ...
    // return val in pVal
    return S_OK;
}
   
    ��Ķ��������������������Ϊ�¼���Ӧ��
    MIDL  interface:  
        HRESULT OnNewObject(IDispatch *p);
        HRESULT OnFreeObject();
    ��C++�е�ʵ���ǣ�
STDMETHODIMP CTest::OnNewObject(IDispatch *p)
{
    m_os=new IMudos(p);  // m_os��CTest��һ������ΪIMudos *�ĳ�Ա����
    return S_OK;
}
STDMETHODIMP CTest::OnFreeObject()
{
    delete m_os;
    return S_OK;
}
    ������COM�о���ʹ��IMudos�����й��ܡ�
    


��¼һ    V21���mudlibתV22��ʱӦע�������

   �����ԭ���õ���MudOS v21.xx, ��������v22��Ҫ�������¸Ķ���

1��ɾ�������ļ�����������ⲿʹ�õĺ���ǰ���private�ؼ��֡�
   ���߼򵥵�ɾ�����к���ǰ���private�����ˡ�
���磺/feature/attack.c�еģ�
private int attack()
....
��Ϊ int attack()

���Ƶ�������У�
  /feature/action.c, treemap.c �ȡ�

2��ע�⺯������������Ҫ�뺯��ʵ��������ͬ
���磺
void myfunction();
....

int myfunction()
{
...
}

��v21�����û���⣬v22��Ͳ�����ȷִ�С�

3����������õ�����ָ��ĵط���

v22����֧������(: ob, string :)�����ĺ���ָ�����ͣ�

����Ҫ�ĳɣ�(: call_other, ob, string :)
�������ļ�: /cmds/std/suicide.c �е�44��
     me->start_busy( (: __FILE__, "slow_suicide", me :));
����ĳɣ�
     me->start_busy( (: call_other, __FILE__, "slow_suicide", me :));
������ȷʹ�á�

���Ƶ��ļ����У�
   es2: /std/weapon/sword.c blade.c axe.c ...
   xkx: /inherit/weapon/sword.c blade.c axe.c ...
�ȵȡ�

4���޸�origin.h
����v22�޸���origin�����ķ�������(��int��Ϊstring),
����Ҫ�޸�origin.h:

#define ORIGIN_BACKEND       0x1
#define ORIGIN_DRIVER        0x1
#define ORIGIN_LOCAL         0x2
#define ORIGIN_CALL_OTHER    0x4
#define ORIGIN_SIMUL_EFUN    0x8
#define ORIGIN_CALL_OUT      0x10
#define ORIGIN_EFUN          0x20

��Ϊ��

#define ORIGIN_DRIVER        "driver"
#define ORIGIN_LOCAL         "local"
#define ORIGIN_CALL_OTHER    "call_other"
#define ORIGIN_SIMUL_EFUN    "simul"
#define ORIGIN_CALL_OUT      "call_out"
#define ORIGIN_EFUN          "efun"

5��SAVE_EXTENSION��
��һЩES2��XKX�汾�� /feature/save.c �У�save_file��load_file�Ĵ�������
��ͬ��������һ������SAVE_EXTENSION����һ��û��SAVE_EXTENSION����ᵼ��
securityd.c�е�valid_write�����д����ļ�ʱ�����⡣ԭ���Ͻ� /feature/save.c
�е�SAVE_EXTENSIONȥ����Ȼ���޸�securityd.c valid_write�����û����̵�һ
�δ���ĳɣ�

      // Let user save their save file
      if( func=="save_object" ) {
              if(
                  sscanf(file, "/data/%*s") &&
                  (
                      ( file == (string) user->query_save_file() )||
                      ( file == (string) user->query_save_file() + ".o")
                  )
              )
              return 1;
      }

6��/cmds/arch/callouts.c
����V22���call_out_info()�������˸Ķ������ٷ���call_out�Ĳ�����Ҳ����˵
���ص�info[i]û��info[i][3]�������Ҫ��һ��/cmds/arch/callouts.c������
info[i][3]������ȥ����


��¼��    Mudos v22pre11 with COM extension�е�COM����

mudos.idl�ļ�
// Generated .IDL file (by the OLE/COM Object Viewer)
// 
// typelib filename: MUDOS.DLL
// Forward declare all types defined in this typelib
interface IMValue;
interface IMNumber;
interface IMString;
interface IMReal;
interface IMObject;
interface IMClass;
interface IMMapping;
interface IMArray;
interface IMBuffer;
interface IMProgram;
interface IMFunction;
interface IMudos;

[
  uuid(F64617C2-EA5A-11D1-B962-0080AD1480B3),
  version(1.0),
  helpstring("mudos v22pre11 Type Library")
]
library MUDOSLib
{
    // TLib : OLE Automation : {00020430-0000-0000-C000-000000000046}
    importlib("STDOLE2.TLB");

    [
      uuid(1B6ED8C0-EB38-11D1-BF0B-0000B4560A15),
      helpstring("MValue Class")
    ]
    coclass MValue {
        [default] interface IMValue;
        interface IMNumber;
        interface IMString;
        interface IMReal;
        interface IMObject;
        interface IMClass;
        interface IMMapping;
        interface IMArray;
        interface IMBuffer;
    };

    [
      odl,
      uuid(1B6ED7C8-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMValue Interface"),
      dual,
      oleautomation
    ]
    interface IMValue : IDispatch {
        [id(0x00000051), propget, helpstring("property Name")]
        HRESULT _stdcall Name([out, retval] BSTR* pVal);
        [id(0x00000052), propget, helpstring("property Type")]
        HRESULT _stdcall Type([out, retval] eVALUETYPE* pVal);
        [id(0x00000053), helpstring("method CreateNumber")]
        HRESULT _stdcall CreateNumber();
        [id(0x00000054), helpstring("method CreateString")]
        HRESULT _stdcall CreateString();
        [id(0x00000055), helpstring("method CreateReal")]
        HRESULT _stdcall CreateReal();
        [id(0x00000056), helpstring("method CreateArray")]
        HRESULT _stdcall CreateArray([in] int size);
        [id(0x00000057), helpstring("method CreateMapping")]
        HRESULT _stdcall CreateMapping();
        [id(0x00000058), propget, helpstring("property Extend")]
        HRESULT _stdcall Extend([out, retval] IDispatch** pVal);
    };

    typedef enum {
        VP_UNKNOW = 0,
        VP_NUMBER = 1,
        VP_STRING = 2,
        VP_REAL = 3,
        VP_OBJECT = 4,
        VP_ARRAY = 5,
        VP_MAPPING = 6,
        VP_CLASS = 7,
        VP_BUFFER = 8,
        VP_FUNCTION = 9
    } eVALUETYPE;

    [
      odl,
      uuid(1B6ED7C0-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMNumber Interface"),
      dual,
      oleautomation
    ]
    interface IMNumber : IDispatch {
        [id(0x00000001), propget, helpstring("property Number")]
        HRESULT _stdcall Number([out, retval] int* pVal);
        [id(0x00000001), propput, helpstring("property Number")]
        HRESULT _stdcall Number([in] int pVal);
    };

    [
      odl,
      uuid(1B6ED7C1-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMString Interface"),
      dual,
      oleautomation
    ]
    interface IMString : IDispatch {
        [id(0x0000000b), propget, helpstring("property String")]
        HRESULT _stdcall String([out, retval] BSTR* pVal);
        [id(0x0000000b), propput, helpstring("property String")]
        HRESULT _stdcall String([in] BSTR pVal);
    };

    [
      odl,
      uuid(1B6ED7C2-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMReal Interface"),
      dual,
      oleautomation
    ]
    interface IMReal : IDispatch {
        [id(0x00000015), propget, helpstring("property Real")]
        HRESULT _stdcall Real([out, retval] single* pVal);
        [id(0x00000015), propput, helpstring("property Real")]
        HRESULT _stdcall Real([in] single pVal);
    };

    [
      odl,
      uuid(1B6ED7C3-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMObject Interface"),
      dual,
      oleautomation
    ]
    interface IMObject : IDispatch {
        [id(0x0000001f), propget, helpstring("property ObjectName")]
        HRESULT _stdcall ObjectName([out, retval] BSTR* pVal);
        [id(0x00000020), propget, helpstring("property ObjectLoadTime")]
        HRESULT _stdcall ObjectLoadTime([out, retval] int* pVal);
        [id(0x00000021), propget, helpstring("property Environment")]
        HRESULT _stdcall Environment([out, retval] IMObject** pVal);
        [id(0x00000022), propget, helpstring("property ValueCount")]
        HRESULT _stdcall ValueCount([out, retval] int* pVal);
        [id(0x00000023), propget, helpstring("property Value")]
        HRESULT _stdcall Value(
                        [in] int id, 
                        [out, retval] IMValue** pVal);
    };

    [
      odl,
      uuid(1B6ED7C5-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMClass Interface"),
      dual,
      oleautomation
    ]
    interface IMClass : IDispatch {
        [id(0x00000033), propget, helpstring("property MemberCount")]
        HRESULT _stdcall MemberCount([out, retval] int* pVal);
        [id(0x00000034), propget, helpstring("property Member")]
        HRESULT _stdcall Member(
                        [in] int id, 
                        [out, retval] IMValue** pVal);
    };

    [
      odl,
      uuid(1B6ED7C6-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMMapping Interface"),
      dual,
      oleautomation
    ]
    interface IMMapping : IDispatch {
        [id(0x0000003d), propget, helpstring("property MappingCount")]
        HRESULT _stdcall MappingCount([out, retval] int* pVal);
        [id(0x0000003e), propget, helpstring("property MappingKeys")]
        HRESULT _stdcall MappingKeys([out, retval] IMArray** pVal);
        [id(0x0000003f), helpstring("method Query")]
        HRESULT _stdcall Query(
                        [in] BSTR sKey, 
                        [out, retval] IMValue** pVal);
        [id(0x00000040), helpstring("method Map")]
        HRESULT _stdcall Map(
                        [in] BSTR sKey, 
                        [in] IMValue* pVal);
    };

    [
      odl,
      uuid(1B6ED7C4-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMArray Interface"),
      dual,
      oleautomation
    ]
    interface IMArray : IDispatch {
        [id(0x00000029), propget, helpstring("property ItemCount")]
        HRESULT _stdcall ItemCount([out, retval] int* pVal);
        [id(0x0000002a), propget, helpstring("property Item")]
        HRESULT _stdcall Item(
                        [in] int id, 
                        [out, retval] IMValue** pVal);
    };

    [
      odl,
      uuid(1B6ED7C7-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMBuffer Interface"),
      dual,
      oleautomation
    ]
    interface IMBuffer : IDispatch {
    };

    [
      uuid(1B6ED8C1-EB38-11D1-BF0B-0000B4560A15),
      helpstring("MProgram Class")
    ]
    coclass MProgram {
        [default] interface IMProgram;
    };

    [
      odl,
      uuid(1B6ED7C9-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMProgram Interface"),
      dual,
      oleautomation
    ]
    interface IMProgram : IDispatch {
        [id(0x00000001), propget, helpstring("property FunctionCount")]
        HRESULT _stdcall FunctionCount([out, retval] int* pVal);
        [id(0x00000002), propget, helpstring("property Function")]
        HRESULT _stdcall Function(
                        [in] int id, 
                        [out, retval] IMFunction** pVal);
        [id(0x00000005), propget, helpstring("property FileName")]
        HRESULT _stdcall FileName([out, retval] BSTR* pVal);
    };

    [
      odl,
      uuid(1B6ED7CA-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMFunction Interface"),
      dual,
      oleautomation
    ]
    interface IMFunction : IDispatch {
        [id(0x00000001), propget, helpstring("property Name")]
        HRESULT _stdcall Name([out, retval] BSTR* pVal);
        [id(0x00000002), propget, helpstring("property ParamCount")]
        HRESULT _stdcall ParamCount([out, retval] int* pVal);
        [id(0x00000003), helpstring("method AddParam")]
        HRESULT _stdcall AddParam([in] IMValue* pVal);
        [id(0x00000004), helpstring("method ClearParam")]
        HRESULT _stdcall ClearParam();
        [id(0x00000005), propget, helpstring("property Ret")]
        HRESULT _stdcall Ret([out, retval] IMValue** pVal);
        [id(0x00000006), helpstring("method Apply")]
        HRESULT _stdcall Apply();
    };

    [
      uuid(1B6ED8C2-EB38-11D1-BF0B-0000B4560A15),
      helpstring("MFunction Class")
    ]
    coclass MFunction {
        [default] interface IMFunction;
    };

    [
      uuid(1B6ED8C3-EB38-11D1-BF0B-0000B4560A15),
      helpstring("Mudos Class")
    ]
    coclass Mudos {
        [default] interface IMudos;
    };

    [
      odl,
      uuid(1B6ED7CB-EB38-11D1-BF0B-0000B4560A15),
      helpstring("IMudos Interface"),
      dual,
      oleautomation
    ]
    interface IMudos : IDispatch {
        [id(0x00000001), propget, helpstring("property CurrentObject")]
        HRESULT _stdcall CurrentObject([out, retval] IMObject** pVal);
        [id(0x00000002), propget, helpstring("property CurrentProgram")]
        HRESULT _stdcall CurrentProgram([out, retval] IMProgram** pVal);
        [id(0x00000003), helpstring("method SetCommHook, pFunc is the function address.
int commhook(char *buf,int cursize,int maxsize,int user_id)")]
        HRESULT _stdcall SetCommHook([in] int pFunc);
        [id(0x00000004), helpstring("method Shutdown")]
        HRESULT _stdcall Shutdown();
        [id(0x00000005), propget, helpstring("property Users")]
        HRESULT _stdcall Users([out, retval] IMArray** pVal);
        [id(0x00000006), helpstring("method GetUser")]
        HRESULT _stdcall GetUser(
                        [in] int UserId, 
                        [out, retval] IMObject** pVal);
        [id(0x00000007), propget, helpstring("property HeartBeat")]
        HRESULT _stdcall HeartBeat([out, retval] int* pVal);
        [id(0x00000007), propput, helpstring("property HeartBeat")]
        HRESULT _stdcall HeartBeat([in] int pVal);
    };
};



��MUDOS COM�������������VC5��classwizard�Զ�����Mudos.h �� Mudos.cpp��
Ȼ����mudos.h�м������¶��壨��Щֵ��IMValue::Type()�ķ���ֵ��
#define        VP_UNKNOW        0
#define        VP_NUMBER        ( VP_UNKNOW  + 1 )
#define        VP_STRING        ( VP_NUMBER  + 1 )
#define        VP_REAL          ( VP_STRING  + 1 )
#define        VP_OBJECT        ( VP_REAL    + 1 )
#define        VP_ARRAY         ( VP_OBJECT  + 1 )
#define        VP_MAPPING       ( VP_ARRAY   + 1 ) 
#define        VP_CLASS         ( VP_MAPPING + 1 )
#define        VP_BUFFER        ( VP_CLASS   + 1 )
#define        VP_FUNCTION      ( VP_BUFFER  + 1 )


��¼��    Mudos v22pre11 with COM extension�ļ���

    �����õ�Mudos v22pre11 for WIN95/NT with COM extensionʱ������һ��
zip�ļ�������winzipչ�����������Mudos��Release��ִ�г���Debug��ִ�г���
��ƪ�ĵ�˵����һ��LPC��COM��ͱ�̵����Ӻ�һ�������õ�es2 mudlib��

    Release���Mudosִ�г�����binĿ¼�£�����mudos.exe��mudos.dll�����ļ���
������չ����������ִ�� regsvr32 mudos.dll ��regsvr32��һ��COM����Ǽ��õ�
����һ�����win95��systemĿ¼�¡�������mudos.exe��ͬĿ¼�£��½�һ���ı���
����ȡ��Ϊmudos.ini����������

; mudos.ini
[init]
config=d:\mudlib\es2\config.es2  ; �����mudlib�������ļ�·���������ȫ·����
heartbeat=1000                   ; �����heartbeat��ֵ���Ժ����
addr_port=3990                   ; �����Ҫ����addr_server������ϴ��

[com]
{EAB22AC1-30C1-11CF-A7EB-0000C05BAE0B}=c:\win\system\shdocvw.dll
;ֻ�������ﶨ�����CLSID����ProgID������LPC��ʹ��


    ���ո�¼һ���ṩ��mudlib�޸ķ�����v21���mudlib�ĳ�v22��ġ�
     
    ������õ���WIN95��ֱ������mudos.exe�ͻ�����mud�ˡ������������service
ʹ���´����������ʱ��mud�����Զ����У���ִ�� mudos install
    ������õ���WINNT����ִ�� mudos install�����������㴴������ɹ�ʱ�����
������Control Panel�е�Services�ҵ�mudos v22pre11 ...�������Ȼ��ѡ��start
������mud�ˡ��´ο���ʱ���Զ�����mud��

    ����ʱ����explorer���Ǹ�״̬�����Ҷ˼���һ��"С����"��ICON���Դ˱�������
�����С�������Ҽ�������������һ���˵�������ѡ��restart��shutdown��
   
    DebugĿ¼����Debug���Mudos���÷���Releaseһ�����ڵ���COM����ʱ��Debug��
�ȽϷ��㣨Release���а����е��쳣���ص��ˣ���

    TestSrcĿ¼����һ��LPC��COM��ͱ�̵����ӡ���VC5���롣

    AppleĿ¼����һ���ѱ���õ�ƻ��������ӣ�ʹ��ʱ��ִ�� regsvr32 apple.dll��
��duke.c����ĳ��npcĿ¼�£���mudos.ini��com�ֶ��м���
    {B3C3EDB1-E735-11D1-BF0B-0000B4560A15}=1
    �����Ϳ���clone duke������һ������ƻ����Ļ����ˣ���ɫ���ˡ�


