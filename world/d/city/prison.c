
// by canoe
#include <ansi.h>
inherit ROOM;

void create()
{
set("short",HIR"�������"NOR);
set("long",@LONG
����һƬ���,���߲�ʱ������ι�.����ԼԼ�Ĺ�Ӱ��������.
����ɢ��ܶ��̾�,�⾹Ȼ���Ǵ�˵�еİ������!
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
 me->set("startroom","/d/city/prison.c");
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
   return 1;
}
int do_out()
{
object me=this_player();
call_other("/daemon/condition/maren.c", "???");
if(!me->query_condition("maren")) 
      { message_vision("$N�����ͷţ�$N��ת�Ƶ���ջ��\n"NOR,me);
                me->move("/d/city/kezhan");
                      me->set("startroom","/d/city/kezhan");
                      me->save();
              }
     else message_vision("$N��ͼ�뿪�����ϧ����û����\n"NOR,me);
 return 1;
}
