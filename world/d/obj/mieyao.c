

//����������

#include <ansi.h>
#define SHILI_D "/adm/daemons/shili"
#define YAODIR_ "/d/obj/yao/"

string* listxian=({
	"yao-moon",
	"yao-fangcun",
	"yao-putuo",
	"yao-dragon",
	"yao-wzg",
	"yao-kunlun",
	"yao-pansi",
	"yao-hell",
	"yao-wudidong",
	"yao-xueshan",
	"yao-jjf",
});

string* listyao=({
	"yao-hell",
	"yao-wudidong",
	"yao-xueshan",
//	"yao-gumu",
	"yao-pansi",
});


string *dirs = ({
"baoxiang",
"biqiu",
"chechi",
"fengxian",
"jinping",
"jisaiguo",
"nuerguo",
"tongtian",
"qinfa",
"tianzhu",
//"wudidong",
"wuji",
"yuhua",
"zhuzi",
});

//int add_new_yao( object me);
//string add_new_yao(string str);
void create()
{
    seteuid(getuid());
}

string query_family_type(string fam)
{
    if(fam=="��������"||fam=="����ɽ���Ƕ�"||fam=="��ׯ��"||fam=="����ɽ���鶴"||
	fam=="�¹�"||fam=="�Ϻ�����ɽ"||fam=="������")
	return "xian";
    return "yao";
}


string add_new_yao(object me)
//string add_new_yao(string str)
{
   string loc,fam,pos;
   string mytype,yaotype,postype;
   object yao;
   string str;
   int lvl=me->query_temp("mieyao/level2");
   string yaoid;
    string yaoname,*yaoids;
   me->set("mieyao_time",time());
   me->delete("mieyao/done2");
   pos=dirs[random(sizeof(dirs))];
   loc="/d/qujing/"+pos;
   mytype=query_family_type(me->query("family/family_name"));
//      fam=SHILI_D->query("family");
      fam=SHILI_D->query_family(pos);
    postype=query_family_type(fam);
   if(mytype=="xian")yaotype="yao";
   else yaotype="xian";

   //if(yaotype=="xian"){
   	yao=new(YAODIR_+listxian[random(sizeof(listxian))]);
   //}else{
   //	yao=new(YAODIR_+listyao[random(sizeof(listyao))]);
   //}

    yaoname=yao->query("name");
    yaoids=yao->parse_command_id_list();
    yaoid=me->query("id")+"'s "+yaoids[0];
    yaoids=({yaoid})+explode(yaoid," ");
    yao->set_name(yaoname,yaoids);
   yao->set("pos",pos);

      str=yao->invocation(me,lvl,loc);
   if(yaotype=="xian"){
   if(mytype!=postype){
       str=str+"һ��������\n����ȥ�������ǵĲ���\n";
   }else if(fam==me->query("family/family_name")){
       str=str+"һ����������, ������Ϊ��\n����ȥ���������ͽ��\n";
   }else {
       str=str+"��"+fam+"�ȼ�ƶ��,\n��ȥ�������ͽ����ɫ������\n";
   }
}else{
if(mytype!=postype){
       str=str+"һ��������\n����ȥ��֮��\n";
   }else if(fam==me->query("family/family_name")){
       str=str+"һ�����ҡ�\n����ȥ����֮��\n";
   }else {
       str=str+"һ�����ҡ�\n����ȥ��"+fam+"����֮��\n";
   }
   }
    me->set("mieyao/name2",yaoname);
    me->set("mieyao/place",SHILI_D->query_chinese(pos));
   return str;
}

string query_yao(object me)
//string query_yao(string str)
{
    mapping mieyao = me->query("mieyao");
    int lvl;
    string str="";
    object yao;

    //if(mapp(mieyao=me->query("mieyao"))){
    if(!me->query("mieyao/done2"))
    {
       	if( mapp(mieyao) && stringp(mieyao["place"]) && stringp(mieyao["name2"]) && time()<me->query("mieyao_time")+600 )
      		return ("��������ȥɱ��"+mieyao["place"]+"��"+mieyao["name2"]+"ô?\n");
        else
        {
         	str="������û�ã����ٸ���һ�λ��ᣡ\n";
         	me->add("faith",-1);
         	lvl=me->query_temp("mieyao/level2");
         	if(lvl>0)lvl--;
         	me->set_temp("mieyao/level2",lvl);
        }
    }
    else if( me->query("mieyao/done2") && time()-me->query("mieyao_time")<100 )
    {
        	return ("�������ˣ��㻹������ȥ��Ϣһ�°ɣ�\n");
    }
    else
    {
    	 lvl=me->query_temp("mieyao/level2");
         lvl++;
         if(lvl==12)lvl=1;
         me->set_temp("mieyao/level2",lvl);
    }
    str+=add_new_yao(me); //�˴���
    return str;
}
