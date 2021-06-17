

//负责存放妖。

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
    if(fam=="东海龙宫"||fam=="方寸山三星洞"||fam=="五庄观"||fam=="昆仑山玉虚洞"||
	fam=="月宫"||fam=="南海普陀山"||fam=="将军府")
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
       str=str+"一带护法。\n你速去扰乱他们的部署！\n";
   }else if(fam==me->query("family/family_name")){
       str=str+"一带积德行善, 胆大妄为。\n你速去吃了这个狂徒。\n";
   }else {
       str=str+"替"+fam+"救济贫民,\n你去给这个狂徒点颜色看看。\n";
   }
}else{
if(mytype!=postype){
       str=str+"一带护法。\n你速去灭之！\n";
   }else if(fam==me->query("family/family_name")){
       str=str+"一带扰乱。\n你速去消灭之。\n";
   }else {
       str=str+"一带扰乱。\n你速去助"+fam+"消灭之。\n";
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
      		return ("不是让你去杀了"+mieyao["place"]+"的"+mieyao["name2"]+"么?\n");
        else
        {
         	str="你真是没用，我再给你一次机会！\n";
         	me->add("faith",-1);
         	lvl=me->query_temp("mieyao/level2");
         	if(lvl>0)lvl--;
         	me->set_temp("mieyao/level2",lvl);
        }
    }
    else if( me->query("mieyao/done2") && time()-me->query("mieyao_time")<100 )
    {
        	return ("辛苦你了，你还是先下去休息一下吧！\n");
    }
    else
    {
    	 lvl=me->query_temp("mieyao/level2");
         lvl++;
         if(lvl==12)lvl=1;
         me->set_temp("mieyao/level2",lvl);
    }
    str+=add_new_yao(me); //此处改
    return str;
}
