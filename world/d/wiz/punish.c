// by canoe
#include <ansi.h>
inherit ROOM;
void create()
{
set("short",HIR"��Ƥ����"NOR);
set("long",@LONG
����һƬ���,���߲�ʱ������ι�.����ԼԼ�Ĺ�Ӱ��������.
����ɢ��ܶ��̾�,�⾹Ȼ���Ǵ�˵�еİ�Ƥ����!
�������Ϊ���Ӷ��ˣ������á�jinshi�����������ʳ�
�������Ϊ����������ˣ������á�out�����뿪���

LONG
);
set("valid_startroom",1);
}
void init ()
{
object me=this_player();
     if(!wizardp(me))
{
 add_action("block_cmd","",1);      
 add_action("do_out","out");      
add_action("do_jinshi","jinshi");      
 me->set("startroom","/d/wiz/dalao.c");
 me->save();
}
}
int block_cmd()
{
        string verb = query_verb();
   
   if (verb=="say") return 0; //allow say
   if (verb=="help") return 0;
   if (verb=="out") return 0;
   if (verb=="look") return 0;
  if (verb=="hp") return 0;
   if (verb=="jinshi") return 0;
   return 1;
}
int do_out()
{
object me=this_player();
//call_other("/daemon/condition/maren.c", "???");
if(me->query("mud_age")-me->query("tongji/mudage")>3600) 
      { message_vision("$N�����ͷţ�$N��ת�Ƶ���ջ��\n"NOR,me);
                me->move("/d/city/kezhan");
                me->delete("tongji/pktime");
if(me->query("combat_exp")>50000) me->add("combat_exp",-50000);
                me->set("startroom","/d/city/kezhan");
  tell_object(me,"��ΪPK�ĳͷ����㱻����50000��ѧ��\n");
                me->save();
              }
     else message_vision("$N��ͼ�뿪�����ϧ����û����\n"NOR,me);
 return 1;
}
int do_jinshi()
{
object me=this_player();
  if((int)me->query("food")<100||(int)me->query("water")<100) 
      { 
      message_vision("���俴��$N�����ꤵ����ӣ�͵͵����$Nһ�����Ӻ�һƿˮ��\n"NOR,me);
message_vision("$N�м����͸�����һǧ��ѧ��Ϊ���ꡣ\n"NOR,me);
       me->set("food",1000);
       me->set("water",1000);
if(me->query("combat_exp")>1000) me->add("combat_exp",-1000);
      me->save();
      }
     else message_vision("$N������Ҫ�����ԣ���ϧ���䲻����\n"NOR,me);
 return 1;
}
