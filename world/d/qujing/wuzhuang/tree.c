//Cracked by Roath

//  ����֮�� ������
//  by happ@YSZZ 2000.4.9
//  /d/qujing/wuzhuang/tree.c

#include <room.h>
inherit ROOM;
#include <ansi.h>
int do_jie();
void create ()
{
   set ("short", "�˲ι���");
   set ("long", @LONG

����һ���˲ι��������Ǹ���֦�������Ҷ��ɭ����Ҷ��ȴ�ưŽ�
ģ����ֱ��ȥ��ǧ�߶�ߣ��������߰�����Χ�����ϵ�֦�ϣ�¶��
һ���˲ι������������һ�㣬������������졣
��������һ�����Ӳӵķ�ӡ��������Խң�jie��������
LONG);

   set("exits", 
   ([ //sizeof() == 4
        "up" : __DIR__"shugan1",
        "south": __DIR__"baicaidi",
   ]));
   
   setup();
}

int valid_leave(object me, string dir)
{
        if ( dir == "south" && me->query_temp("kill_tree") )
                {
        tell_object(me,HIY"��Ȼ�������һ�����֣�һ�¾Ͱ���ץ���ˣ�ԭ������Ԫ���ɡ�\n"NOR);
        me->move("/d/qujing/wuzhuang/chengyun");
        return notify_fail(HIC"�����ﰵ�룬�������ˡ�\n"NOR);
                }
        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_jie","jie");
}

int do_jie()
{
	object me = this_player();
	object jingang;
	if( !me->query_temp("huohun/yuanshen") )
		return 0;
	else if( me->query_temp("huohun/tu") )
	{
		message_vision("\n�����ӡ���Ѿ�����ҿ��ˣ�\n",me);
		return 1;
	}
	else
	{
		me->add_temp("huohun/yuanshen",1);
		me->set_temp("huohun/tu",1);
		message_vision(HIY"\n$N���Ὣ��ӡ�ҿ���һ����â�ɳ�������ɽ����ƶ������ȥ��\n"NOR,me);
		message_vision(HIY"\n��Ȼ������������������λ��գ������ȵ���˭��˽�Խҿ���ӡ����\n",me);
		jingang = new("/d/qujing/kusong/npc/jingang");
		jingang->move(environment(me));
		jingang->kill_ob(me);
		jingang = new("/d/qujing/kusong/npc/jingang");
		jingang->move(environment(me));
		jingang->kill_ob(me);
		return 1;
	}
}