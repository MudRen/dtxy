//Cracked by bear
inherit ROOM;
#include <ansi.h>
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();

void create ()
{
  set ("short", "������");
  set ("long", @LONG

������ǻ��ƶ������ģ������á���ǰ��һ�Ѻڻ�Ƥ�����θ߸�
���ϣ��κ�һ����ɫ����죬�������š�ʥӤ�������ĸ����ӡ�
����С��������ͷ����ʮ�����͵ư������յ�ѩ����
LONG);
  set("exits", ([ /* sizeof() == 4 */
  "south" : __DIR__"yongdao7",
  "west" : __DIR__"jin",
  "east" : __DIR__"tu",
  "northeast" : __DIR__"huo",
  "northwest" : __DIR__"mu",
  "north" : __DIR__"shui", 
]));

  set("objects", ([ /* sizeof() == 1*/
  __DIR__"npc/honghaier" : 1,
  __DIR__"obj/che1" : 1,
  __DIR__"obj/che2" : 1,  
  __DIR__"obj/che3" : 1,  
  __DIR__"obj/che4" : 1,  
  __DIR__"obj/che5" : 1,  
]));


  setup();
  
//   call_other("/obj/board/kusong_b", "???")
}
void init()
{
   //object where=this_object();

   // remove_call_out("check_time");
   //check_time(where);
   //add_action("do_hear","hear");
}
void check_time(object where)
{

   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];
   int phase=((int)(t/120));
   if(phase==0&&(!query("jiangjing"))) jiang_jing(where);
if(phase==7&&query("jiangjing")) finish_jing(where);
   call_out("check_time",60,where);
}

void jiang_jing(object where)
{
message("channel:es",CYN+"��"YEL"���ɽ����ƶ�"CYN"��"YEL"�캢��[Honghai er]"CYN"�����ڿ�ʼ�������ǿ��ɽ����ƶ���ħ����\n"+NOR,users());
tell_object(where,"�캢��˵�������˿��ɽ����ƶ��Ķ���Ҳ��\n");
tell_object(where,"��ħ�ķ���������������������Ǵ�������Ҳ����һ�٣�\n");
tell_object(where,"��������ħ��Ŀ����ϣ���ܲ�͸��ؼ�����İ��أ��Դﵽ���˺�һ�ľ��硣\n");

   tell_object(where,"ע�⣺ɽ����ɽ���������졣\n");
   set("jiangjing",1);
}
void finish_jing(object where)
{
   tell_object(where,"�캢��˵������ȥ��������ķ���չ��Ρ�\n");
   set("jiangjing",0);
     set ("long", @LONG
   ���ƶ����Ӱ��������� �����������캢�����ڱ����ķ���
LONG);
}
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
      return notify_fail("�캢����û��ʼ���ڱ����ķ��ء�\n");

 if((string)me->query("family/family_name")!="���ƶ�")
      return notify_fail("���ɵ��Ӳ�����������\n");
   if(me->query("faith")>40000)
      return notify_fail("��ı����ķ��Ѿ������������ˡ�\n");

    tell_object(me,"�����Ա����ţ����š������Ա����ķ���������\n");
   me->start_busy(5);
   me->improve_skill("huomoforce",random((int)(me->query("spi")+me->query("int"))/2));
   me->improve_skill("pingtian-dafa",random((int)(me->query("spi")+me->query("int"))/2));
//  me->add("faith",1);
//  me->add("combat_exp",30);
//  me->add("potential",10);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   return 1;
}

