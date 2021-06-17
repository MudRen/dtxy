// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// inside3.c
#include <ansi.h>
void check_time(object where);
void feel_hungry(object where);
void feel_full(object where);
int do_serve();
inherit ROOM;

void create ()
{
  set ("short", "��������");
  set ("long", @LONG

����֮����һ���飬��ŵ��һ���յ�ͨ��������������ʯ������ɣ�����
���л�Ƕ�������鱦������ǽ�Ϲ������������������൱�ĳ¾ɡ�������
�ϱ�������ƫ�����������ˣ��㻹���Ը�������һ�¡�(serve)

LONG);

  set("exits", ([ /* sizeof() == 2 */
  "westdown" : __DIR__"inside2.c",
  "east" : __DIR__"inside4",
]));
  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/longwang" : 1,
]));
  set("water", 1);
  setup();

}

void init()
{
   object where=this_object();

  remove_call_out("check_time");
   check_time(where);
   add_action("do_serve","serve");
}

void check_time(object where)
{
   mixed *local = localtime(time()*60);
   int t = local[2] * 60 + local[1];
  int phase=((int)(t/120));
if((phase==1)&&(!query("hungry"))) feel_hungry(where);
if((phase==2)&&query("hungry")) feel_full(where);
   call_out("check_time",60,where);
}

void feel_hungry(object where)
{
message("channel:es",HIG+"����������������(Ao guang)�������ˣ�������������\n"+NOR,users());
   set("hungry",1);
}
void feel_full(object where)
{
tell_object(where,"��������Ц�����ܺã��ܺá�\n");
  set("hungry",0);
}
int do_serve()
{
   object me=this_player();
   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("hungry"))
      return notify_fail("�����������������ڲ��ۣ�\n");
   if((string)me->query("family/family_name")!="��������")
      return notify_fail("����������������������ݣ�\n");
   if(me->query("faith")>5000||me->query("combat_exp")>10000000)
      return notify_fail("����������������ݵ��ˣ��������¾���С�������ɡ�\n");
   tell_object(me,"������̺���ͨ����ˮ�������������������Ħ��\n");
   me->start_busy(5);
      me->add("faith",1);
	  me->improve_skill("seashentong",random((int)(me->query("spi")+me->query("int"))/2),1);
   me->add("combat_exp",9);
   me->add("potential",3);
   me->receive_damage("kee",40);
   me->receive_damage("sen",40);
   tell_object(me,"����ñ̺���ͨ�����ˣ�\n");
   return 1;
}
int valid_leave()
{
    if(
       (present("dao kan dao", this_player()))
       || (present("jiu gu cha", this_player()))
       || (present("mei hua chui", this_player()))
       || (present("hua gan ji", this_player()))
      )
        return notify_fail("�����������������ߣ�\n");
    return ::valid_leave();
}
