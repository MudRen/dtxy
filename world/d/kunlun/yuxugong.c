inherit ROOM;
#include <ansi.h>
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();
void create()
{
        set("short",HIW "���鹬");
        set("long", @LONG
    �������鹬�ˣ���ǰһλ�����������붨������
���������˳�����˵�ͷ��
LONG );
        set("exits", ([
                "south" : __DIR__"hundun8",
        ]));
          set("kunlun", 1);
  set("objects", ([ // sizeof() == 1 //
 __DIR__"npc/tianzun" : 1,
 __DIR__"npc/baihe" : 1,
]));
  set("valid_startroom", 1);
  setup();
}
void init()
{
  //  object where=this_object();
  //  remove_call_out("check_time");
  //  check_time(where);
  //  add_action("do_hear","hear");
}
void check_time(object where)
{
   mixed *local = localtime((time()-900000000)*60);
   int t = local[2] * 60 + local[1];

   int phase=((int)(t/120));
   if(phase==5&&(!query("jiangjing"))) jiang_jing(where);
   if(phase==7&&query("jiangjing")) finish_jing(where);
   call_out("check_time",60,where);
}
void jiang_jing(object where)
{
message("channel:es",HIG+"������ɽ���鶴�������[guang chengzi]��ʦ�������鹬��̳�������������»�ɽ������\n"+NOR,users());
tell_object(where,"������Ԫʼ�����������֪���ۣ�����ƣ�Ϊ����Ϫ��Ϊ����Ϫ�����²��룬������Ӥ����\n");
tell_object(where,"������Ԫʼ�����������֪��ף������裬Ϊ���¹ȡ�Ϊ���¹ȣ��������㣬�������ӡ�\n");
tell_object(where,"������Ԫʼ�����������֪��ף�����ڣ�Ϊ����ʽ��Ϊ����ʽ�����²�߯���������޼���\n");
tell_object(where,"������Ԫʼ�������������ɢ��Ϊ����ʥ����֮����Ϊ�ٳ����ʴ��ǲ��\n");
tell_object(where,"........................................\n");
   set("jiangjing",1);
}
void finish_jing(object where)
{
   tell_object(where,"Ԫʼ����˵�����������ҽ�������ɡ�\n");
   set("jiangjing",0);
}
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
      return notify_fail("Ԫʼ����û�п�̳������\n");

 if((string)me->query("family/family_name")!="����ɽ���鶴")
      return notify_fail("���������²���������\n");
   if(me->query("faith")>40000)
      return notify_fail("Ԫʼ�������˵���������ȥ��Щ�������������ˡ�\n");
   tell_object(me,"�㲻����Ԫʼ����Ľ������������ˡ�\n");
   me->start_busy(5);
//   me->add("faith",1);
   me->improve_skill("yuxu-spells",random((int)(me->query("spi")+me->query("int"))/2));
//   me->add("combat_exp",30);
//   me->add("potential",5);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   tell_object(me,"����������ɷ������ˣ�\n");
   return 1;
}
