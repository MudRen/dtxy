//Cracked by Roath
//����ɽ���ɡ�dhxy-evil 2000.7.5

inherit ROOM;

#include <ansi.h>
void jiang_jing(object where);
void finish_jing(object where);
void check_time(object where);
int do_hear();
#include <ansi.h>
void create()
{
        set("short", HIY"���"NOR);
        set("long", @LONG
        ��������ɽ���ɵĴ��ǻ�͵ĵص㡣����Ԫʼ����̫�ϵ�
���������Ͼ��������㰸���������ơ���ǽ���ż���̫ʦ�Σ����Ϸ���
�������š�������������Ϣ�ң��ϱ�������Ĺ㳡�������Ǻ�
LONG);

        set("valid_startroom", 1);
        set("exits", ([
                "south" : __DIR__"square",
                "north" : __DIR__"houdian",
                "northeast" : __DIR__"zhmroom",
        ]));

        set("objects", ([
                __DIR__"npc/jiansheng" : 1,
        ]));

        setup();
//      replace_program(ROOM);
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
message("channel:es",CYN+"��"WHT"��ɽ��"CYN"��"WHT"��ʥ[Jian sheng]"CYN"�����ڿ�ʼ����������ɽ��������\n"+NOR,users());
tell_object(where,"��ʥ˵������ɽ��������ȡɽ��������\n");
tell_object(where,"��������ͻ�Ʒ���֮�����������У�׷�����£��Ǻ��ɳۣ�\n");
tell_object(where,"��������Ŀ����ϣ���ܲ�͸��ؼ�����İ��أ��Դﵽ���˺�һ�ľ��硣\n");

   tell_object(where,"ע�⣺ɽ����ɽ���������졣\n");
   set("jiangjing",1);
}
void finish_jing(object where)
{
   tell_object(where,"��ɽ��˵������ȥ�������������չ��Ρ�\n");
   set("jiangjing",0);
     set ("long", @LONG
   ��ɽ�ɵ��Ӱ��������� ������������ʥ˵Щʲô��
LONG);
}
int do_hear()
{
 object yao;
   object me=this_player();

   if(me->is_busy())
      return notify_fail("����æ���ء�\n");
   if(!query("jiangjing"))
      return notify_fail("��ʥ��û��ʼ���ڷ���֮���ء�\n");

 if((string)me->query("family/family_name")!="��ɽ��")
      return notify_fail("���ɵ��Ӳ�����������\n");
   if(me->query("faith")>40000)
      return notify_fail("��ķ���֮���Ѿ����������ˡ�\n");

    tell_object(me,"�����Ա����ţ����š������Է���֮����������\n");
   me->start_busy(5);
   me->improve_skill("zixia-shengong",random((int)(me->query("spi")+me->query("int"))/2));
   me->improve_skill("taoism",random((int)(me->query("spi")+me->query("int"))/2));
//  me->add("faith",1);
//  me->add("combat_exp",30);
//  me->add("potential",10);
   me->receive_damage("kee",20);
   me->receive_damage("sen",20);
   return 1;
}
int valid_leave(object me, string dir)
{
        if (me->query("family/master_id") == "master swordsman")        
        return ::valid_leave(me, dir);
   if (dir == "northeast" ) {
        if (objectp(present("master swordsman", environment(me))))
   return notify_fail("һ�����ص�������ֹ���㣬Ҳ���ǽ�ʥ��������\n");
        }   
        return ::valid_leave(me, dir);
}
