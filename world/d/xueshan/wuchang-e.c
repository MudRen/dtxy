// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
//standroom.c used by weiqi...others may hate this format:D
//icegate.c
#include <ansi.h>
inherit ROOM;
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);           
int do_hear();
void create ()
{
   set ("short", "���䳡");
   set ("long", @LONG

������ȥ����������ͨ��ѩ����������Ρ��׳�ۡ����Ǵ˿̹���
���գ�һλ�������׵�׳����һλ��Ŀ��ɭ��������������ŵ�
������ǰ��
LONG);

   //set("item_desc", ([" *** " : " *** \n", ]));
   //for look something.

   set("exits", 
   ([ //sizeof() == 4
     "south" : __DIR__"wuchang-se",
     "north" : __DIR__"wuchang-ne",
     "west" : __DIR__"wuchang-c",
     //"north" : __DIR__"icegate",
//"west" : __DIR__"wuchang-nw",
//"east" : __DIR__"wuchang-ne",
     //"up" : __DIR__"***",
     //"down" : __DIR__"***",
   ]));
   
   set("objects", 
   ([ //sizeof() == 1
     __DIR__"npc/tuying-zunzhe" : 1,
     __DIR__"npc/baixiang-zunzhe" : 1,
   ]));


   set("outdoors", "xueshan");

   setup();
}


void init()
{
   //object where=this_object();

    //remove_call_out("check_time");
  // check_time(where);
  // add_action("do_hear","hear");
}
void check_time(object where)                
{
   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];
   int phase=((int)(t/120));
   if(phase==4&&(!query("jiangjing"))) jiang_jing(where);
   if(phase==5&&query("jiangjing")) finish_jing(where);
   call_out("check_time",60,where);
}
void jiang_jing(object where)
{
message("channel:es",CYN+"��"WHT"��ѩɽ"CYN"��"WHT"��������[Baixiang zunzhe]"CYN":ѩɽ���ӣ����ڿ�ʼ���ڵ��ɴ�. \n"+NOR,users());
   tell_object(where,"���ɴ󷨿�ν������������������ص��ɷ�.\n");
   set("jiangjing",1);
     set ("long", @LONG
        �ͼ���СС�ĵط����ж�ʮ�������һ�������
  С���������������߽��ɷ�.
LONG);
}
void finish_jing(object where)
{
   set("jiangjing",0);
}
int do_hear()
{
   object me=this_player();
   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
      return notify_fail("�������߻�û��ʼ�ڷ���.\n");              
   if((string)me->query("family/family_name")!="��ѩɽ")
      return notify_fail("���ɵ��Ӳ�����������\n");
    if(me->query("faith")>40000)
      return notify_fail("������Լ������������ˡ�\n");
    tell_object(me,"�������������������򣬲���ü����Ц��\n");
   me->start_busy(5);
   me->improve_skill("dengxian-dafa",random((int)(me->query("spi")+me->query("int"))/2));
//  me->add("faith",1);
//  me->add("combat_exp",12);
//  me->add("potential",3);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   return 1;
}                                                                    

