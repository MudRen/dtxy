// suit.c
// ��ʦ���������кܶ�ԽȨ�ĵط�
// ���ɴ˷������������Ȿվ�Ų�����

#include <mudlib.h>
#include <ansi.h>
#include <armor.h>
#include <command.h>
#define NULL_VALUE 0
inherit CLOTH;
inherit F_SAVE;
inherit F_AUTOLOAD;
inherit F_DAMAGE;
//inherit F_CLEAN_UP;
inherit F_COMMAND;
string replace_color(string,int);
int help(object);
int wiz_set(string,string,string,int);
string inputstr,verb;
int main(object me, string arg);

void create()
{
       seteuid(getuid());
       set_name(HIW"��ʦ������"NOR,({"wizard suit","suit" }));
       set("long",@LONG
��������������������������������������������������������
��  ��  ��  ��    ��       ��   ��    ˵        ��    ��
��������������������������������������������������������
��bianxing  ��bianxing <id>     ����������������      ��
��xing      ��xing <id>         ����ĳ������          ��
��hun       ��hun  <id>         ����ĳ���ε�          ��
��feng      ��feng <id>         ���ⶳĳ��            ��
��jiefeng   ��jiefeng <id>      �����ĳ��            ��
��age       ��age <id> <s>      ���޸�����            ��
��level     ��level <id>        ���鿴�����ս����    ��
��������������������������������������������������������
LONG
       );
       if(clonep())
           set_default_object(__FILE__);
       else{
           set("unit","��");
           seteuid(geteuid());
           set("material", "cloth");
           set("armor_prop/armor", 10000);
           set("no_get",1);
           set("no_drop",1);
           }
       setup();
}
// ����ֱ��
void init()
{
       if( wizardp(environment()) ) {
       add_action("xing","xing");
       add_action("hun","hun");
       add_action("bx","bianxing");
       add_action("fengplayer","feng");
       add_action("nicks","nicks");
       add_action("jiefengplayer","jiefeng");
       add_action ("age", "age");              
       this_player()->set_temp("heat",1);
      }
}


// AGE ����
int age(string str)
{
        object me,target;
        string name;
        int level;
        me=this_player();
        if(!str) return notify_fail("age sb ���ӵ����.\n");
        if(sscanf(str,"%s %d",name,level)==2)   {
        if(!(target=present(name,environment(me))))
                return notify_fail("û��û����ô���ˡ�\n");
        target->add("mud_age",86400*level);
        target->add("age",level);
        write("�޸�"+WHT+target->query("name")+NOR+"���������"+HIR+(string)level+NOR+"�ꡣ\n",this_object());
        return 1;
        }
        else
        return notify_fail("age sb. ���ӵ���͡�\n");
}

// ���˷�ס
int fengplayer (string str)
{
  object ob;
  if(str=="kittt") return notify_fail("���ǲ�����������\n");
  if (!str) return notify_fail("feng <id>\n");
       ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("���������?\n");
  tell_object(ob,"����۾�ͻȻһƬģ��������������ס����...\n");
  ob->set_temp("block_msg/all",1);
  ob->disable_player(HIR "<ʧȥ֪����>" NOR);      
  return 1;    
}
// ���˽��
int jiefengplayer (string str)
{
  object ob;
  if (!str) return notify_fail("jiefeng <id>\n");
       ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("���������?\n");   
  ob->set_temp("block_msg/all",0);
  ob->enable_player(); 
  tell_object(ob,"���˺���˵��������ϲ���ơ��������ڿ���...\n");
  return 1;
}
//  XING ʹ������
int xing (string str)
{
  object who;
  if (!str) return notify_fail ("xing <id>\n");
  who = LOGIN_D->find_body(str);
  if (!who){ 
  if (!(who=present (lower_case(str), environment(this_player()))) )
    return notify_fail ("û��"+str+"ѽ��\n");}
  who->remove_call_out("revive");
  who->revive();
  who->reincarnate();
  return 1;
}
// HUN ʹ�˻赹
int hun (string str)
{
  object who;
  if (!str) return notify_fail ("����ˣ����Լ�Ū�Σ�\n");
  who = LOGIN_D->find_body(str);
  if (!who){ 
  if (!(who=present (lower_case(str), environment(this_player()))) )
    return notify_fail ("û��"+str+"ѽ��\n");}
  who->remove_call_out("unconcious");
  who->unconcious();
  who->announce();
  return 1;
}
//  BX ��������
int bx(string arg)
{
  object bxid,me;
  me=this_player();
  if(arg=="kittt") return notify_fail("�����̵���������\n");
  if (arg!=NULL_VALUE){
    bxid = LOGIN_D->find_body(arg);
    if (!bxid) return notify_fail("�����Ϻ���û�����ѽ��\n");
    }
  if (arg) {
    if(arg=="kittt") return notify_fail("����������\n");
    if(bxid->query("gender")=="Ů��") bxid->set( "gender", "����" );
    else bxid->set( "gender", "Ů��" );
    message("shout", HIM "��ҥ�ԡ�ĳ�ˣ���˵"+me->query("name")+"�ɹ��Ķ�" 
    +bxid->query("name")+"������һ�α���������\n" NOR,users());
    bxid->save();
    return 1;
  }
}

// nicks�޸�
int nicks(string arg)
{
        string dest;
        object me;
        me = this_player();
        if( !arg ) return help(me);     
        if(sscanf(arg,"-title %s,%s",dest,arg)==2)
        {
                if(!wizardp(me))
                        return notify_fail("�������ֻ������ʦʹ�á�\n");
                if(wiz_level(me)<wiz_level("(arch)")&&(dest!="me"&&dest!=me->query("id")))
                        return notify_fail("���Ȩ�޲����������������\n");
                return wiz_set(dest,arg,"title",1)?1:notify_fail("����ʧ�ܡ�\n");
        }
        if(sscanf(arg,"-name %s,%s",dest,arg)==2)
        {
                if(!wizardp(me))
                        return notify_fail("�������ֻ������ʦʹ�á�\n");
                if(wiz_level(me)<wiz_level("(arch)")&&(dest!="me"&&dest!=me->query("id")))
                        return notify_fail("���Ȩ�޲����������������\n");
                return wiz_set(dest,arg,"title",1)?1:notify_fail("����ʧ�ܡ�\n");
        }  
        if(sscanf(arg,"-id %s,%s",dest,arg)==2)
        {
                if(wiz_level(me)<wiz_level("(arch)"))
                        return notify_fail("�������ֻ��������ִ�С�\n");
                return wiz_set(dest,arg,"id",0)?1:notify_fail("����ʧ�ܡ�\n");
        }
        if(sscanf(arg,"-nick %*s")==1)
                sscanf(arg,"-nick %s",arg);
        if(sscanf(arg,"%s,%s",dest,arg)==2)
        {
                if(wiz_level(me)<wiz_level("(apprentice)"))
                        return notify_fail("�������ֻ����С�����ϼ������ʦִ�С�\n");
                return wiz_set(dest,arg,"nickname",1)?1:notify_fail("����ʧ�ܡ�\n");
        }
        if( strlen(replace_color(arg,0)) > 70 )
                return notify_fail("�º�̫���ˣ�������һ����һ��ġ�����һ��ġ�\n");
        return wiz_set("me",arg,"nickname",1)?1:notify_fail("����ʧ�ܡ�\n");
        write("Ok.\n");
        return 1;
}
int wiz_set(string str1,string str2,string prop,int color_flag)
{
        object ob,me;
        me=this_player(1);
        if(str1=="me")
                ob=this_player(1);
        else
                if(!objectp(ob=present(str1,environment(me))))
                        if(!objectp(ob=find_player(str1)))
                                if(!objectp(ob=find_living(str1)))
                                {
                                        tell_object(me,"���ܷ��ֲ�������("+str1+")��\n");
                                        return 0;
                                }
        if(wiz_level(me)<wiz_level(ob))
        {
                tell_object(me,"���Ȩ�޲�����\n");
                return 0;
        }
        if((prop=="title"&&wizardp(me))||prop=="nickname")
                if(str2=="cancel")
                {
                        ob->delete(prop);
                        message_vision("$N��"+prop+"������ˡ�\n",ob);
                        return 1;
                }
        str2=replace_color(str2,color_flag);
        message_vision("$N��"+prop+"���趨Ϊ:"+str2+"\n",ob);
        ob->set(prop,str2);
        return 1;
}

string replace_color(string arg,int flag)
{
        arg = replace_string(arg, "$BLK$", flag?BLK:"");
        arg = replace_string(arg, "$RED$", flag?RED:"");
        arg = replace_string(arg, "$GRN$", flag?GRN:"");
        arg = replace_string(arg, "$YEL$", flag?YEL:"");
        arg = replace_string(arg, "$BLU$", flag?BLU:"");
        arg = replace_string(arg, "$MAG$", flag?MAG:"");
        arg = replace_string(arg, "$CYN$", flag?CYN:"");
        arg = replace_string(arg, "$WHT$", flag?WHT:"");
        arg = replace_string(arg, "$HIR$", flag?HIR:"");
        arg = replace_string(arg, "$HIG$", flag?HIG:"");
        arg = replace_string(arg, "$HIY$", flag?HIY:"");
        arg = replace_string(arg, "$HIB$", flag?HIB:"");
        arg = replace_string(arg, "$HIM$", flag?HIM:"");
        arg = replace_string(arg, "$HIC$", flag?HIC:"");
        arg = replace_string(arg, "$HIW$", flag?HIW:"");
        arg = replace_string(arg, "$NOR$", flag?NOR:"");
        arg = replace_string(arg, "$BLINK$", flag?BLINK:"");
        if(flag) arg+=NOR;
        return arg;
}
int query_autoload()
{
   if (wizardp(this_player())) return 1;
   else return 0;
}
