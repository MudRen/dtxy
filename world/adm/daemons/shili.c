// by bluewww@yszz

#include <ansi.h>

inherit F_SAVE;

mapping shili=([
"baoxiang": (["���޵ظ�":1000,]),
"biqiu"   : (["�Ϻ�����ɽ":1000,]),
"qinfa"   : (["��ׯ��"    :1000,]),
"chechi"  : (["����ɽ���Ƕ�":1000,]),
"fengxian": (["��������": 1000,]),
"jinping" : (["����ɽ���鶴"  : 1000,]),
"jisaiguo": (["��ɽ��": 1000,]),
"nuerguo" : (["�¹�"    : 1000,]),
"tianzhu" : (["��ѩɽ"  : 1000,]),
"tongtian": (["��������": 1000,]),
"wuji"    : (["���ƶ�"  : 1000,]),
"yuhua"   : (["����ɢ��"  : 1000,]),
"wudidong": (["�ݿ�ɽ�޵׶�" : 1000,]),
"zhuzi"   : (["��˿��"     : 1000,]),
"city" : (["������"     : 1000,]),
]);

mapping MASTERS=(["����ɽ���Ƕ�":"��������", 
                 "�Ϻ�����ɽ":"��������",
                 "��ׯ��":"��Ԫ����",
                 "���޵ظ�":"������",
                 "�¹�":"�϶�",
                 "��������":"����",
                 "��ѩɽ":"��������",
                 "�ݿ�ɽ�޵׶�":"����",
                 "����ɽ���鶴":"Ԫʼ����",
                 "��˿��":"��ϼ����",                                
"������":"�̹�", 
"���ƶ�":"ף��", 
"����ɢ��":"�����", 
"��ɽ��":"��ʥ", 
]);

void create()
{
    seteuid(getuid());
    if ( !restore() && !mapp(shili) ){
        shili = ([]);
    }
}

int remove()
{
    save();
    return 1;
}        

string query_save_file() { return DATA_DIR + "shilid"; }         

string query_family(string pos)
{
        mapping tmp;
        string* nf;
        string cf;
        int max,i=1,nmax;
        
        if(!mapp(tmp=shili[pos]))return "";
        max=values(tmp)[0];
        //write("max="+max+"\n");
        cf = keys(tmp)[0];
        //write("cf="+cf+"\n");
        nmax=0;
        nf=keys(tmp);
        while(i<sizeof(nf))
        {
        	//write("max="+values(tmp)[i]+"\n");
        	//write("cf="+keys(tmp)[i]+"\n");
           	if(values(tmp)[i]>max)
           	{
                	max=values(tmp)[i];
                	cf = keys(tmp)[i];
           	}
           	i++;
        }
        return cf;
}

string query_master(string faname)
{
        return MASTERS[faname];
}

int query_shili(string pos,string faname)
{
        mapping tmp;

        if(!mapp(tmp=shili[pos]))return 0;
        return tmp[faname];
}
 // added by happ@YSZZ 

int query_all_shili(string faname)
{
        mapping tmp;
        int i,n;
        string *quyu;

        if( ! mapp(shili) ) return 0;

        quyu=keys(shili);                     
        
        for( i=0;i<sizeof(shili);i++)
        {
         n=query_shili(quyu[i],faname);
        printf("�ڡ�%-s����%6d������",this_object()->query_chinese(quyu[i]),n);  
       i%2==1?write("\n"):write("            ");
        }
        write("\n");

 return 1;
}



void increase_shili(string pos,string faname,int amount)
{
        mapping tmp;
        
        if(!mapp(tmp=shili[pos]))return;
        if(!tmp[faname])tmp+=([faname:amount]);
        else tmp[faname]+=amount;
        
        if(tmp[faname]>1000)tmp[faname]=1000;
}

void decrease_shili(string pos,string faname,int amount)
{
        mapping tmp;
        
        if(!mapp(tmp=shili[pos]))return;
        if(!tmp[faname])tmp+=([faname:0]);
        else tmp[faname]-=amount;
        
        if(tmp[faname]<0)tmp[faname]=0;
}

string query_chinese(string pos)
{
  mapping diqu=([
     "baoxiang": "�����",
     "biqiu"   : "�����",
     "qinfa"   : "�շ���",
     "chechi"  : "���ٹ�",
     "fengxian": "���ɿ�",
     "jinping" : "��ƽ��",
     "jisaiguo": "������",
     "nuerguo" : "Ů����",
     "tianzhu" : "���ù�",
     "tongtian": "�¼�ׯ",
     "wuji"    : "�ڼ���",
     "yuhua"   : "�񻪸�",
     "wudidong": "�޵׶�",
     "zhuzi"   : "���Ϲ�",
     "city"    : "������",
  ]);
 return diqu[pos];
}
 
