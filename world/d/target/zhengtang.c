// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// zhting.c

inherit ROOM;

#include <ansi.h>
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();

void create ()
{
  set ("short", "���ޱ���");
  set ("long", @LONG

��������������£����������ľ����������޵ظ��������󶼻�
�������ܵ�Ӧ�еĴ��á���ǰһ�Ŵ����������������������Ա�
���Ŵ��й١�
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"new-walk5",
  "north": __DIR__"walk1",
]));
  set("hell", 1);
  set("out_doors", 1);
  set("objects", ([ /* sizeof() == 2 */
  __DIR__"npc/yanluowang" : 1,
//  __DIR__"npc/panguan" : 1,
]));
  setup();
  call_other("/obj/board/shengsi_b", "???");
}

void init()
{
    object where=this_object();
    remove_call_out("check_time");
    check_time(where);
    add_action("do_hear","hear");
}

void check_time(object where)
{
   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];
   int phase=((int)(t/120));
   if(phase==5&&(!query("jiangjing"))) jiang_jing(where);
   if(phase==6&&query("jiangjing")) finish_jing(where);
   call_out("check_time",60,where);
}

void jiang_jing(object where)
{
message("channel:es",HIG+"�����޵ظ���������(Yanluo wang)�����ڸ�������˵˵���ǵĹ���ļ��£�\n"+NOR,users());
tell_object(where,"������(Yanluo wang)����ȥһЩ�з�ʳ��Ϣ�ĵط��Խ⼢����\n");
tell_object(where,"������(Yanluo wang)������ǿ���������ڻ��У������ܿ��ˣ����ⱻ���˺���\n");
tell_object(where,"������(Yanluo wang)���������Ҳ�нײ�֮�֡�\n");
tell_object(where,"������(Yanluo wang)�����ǹ���Ӧ�Ժ�ƽΪ�󣬲�Ҫ�˺��޹���\n");
tell_object(where,"........................................\n");
   set("jiangjing",1);
}
void finish_jing(object where)
{
   tell_object(where,"������˵���������Ϣ�ɡ�\n");
   set("jiangjing",0);
}
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
      return notify_fail("�㻹�ǵȻ������ɡ�\n");
   if((string)me->query("family/family_name")!="���޵ظ�")
      return notify_fail("���ɵ��Ӳ�����������\n");
   if(me->query("faith")>1000)
      return notify_fail("������̾�����������֪���Ļ��డ��\n");
   tell_object(me,"�㲻����ͷ����\n");
   me->start_busy(5);
   me->add("faith",1);
   me->improve_skill("gouhunshu",random((int)(me->query("spi")+me->query("int"))/2),1);
   me->add("combat_exp",30);
   me->add("potential",5);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   tell_object(me,"��Թ���������������ˣ�\n");
   return 1;
}
