//Cracked by Roath
//standroom.c used by weiqi...others may hate this format:D
//tingjing.c

#include <room.h>
inherit ROOM;
#include <ansi.h>
int do_jie();

void create ()
{
	set ("short", "����ʯ");
	set ("long", @LONG

���ʯͷ(stone)״����ֻ���Եĺ��꣬������ſ�ں�̲�ϡ���˵
���������������ɶ�����ȥ͵�����������Ҫ���Ǽ��¾��ģ�
��������ˮ�彲�⡣���ϣ�������������ȫ���ע�¾������
���ش󺣵�ʱ�䣬���Ϊʯͷ��
ʯͷ����һ�����Ӳӵķ�ӡ��������Խң�jie��������
LONG);

	set("item_desc", (["stone" : "ʯͷ�Ͽ���һ��ʫ�� \n
		��˵���������飬
		����������̸����
		������·���ʯ��
		���ǵ��겻������\n", ]));
	//for look something.

	set("exits", 
	([ //sizeof() == 4
		//"south" : __DIR__"***",
		//"north" : __DIR__"wuchang-s",
		"south" : __DIR__"island",
		"north" : __DIR__"shanglu2",
		//"up" : __DIR__"***",
		//"down" : __DIR__"***",
	]));
	
	set("objects", 
	([ //sizeof() == 1
		//__DIR__"npc/***" : 1,
	]));


	set("outdoors", "/d/nanhai");

	setup();
}

//void init()
//{
	//add_action("do_jump", "jump");
//}

//int do_jump(string arg)
//{
       
//}

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
	else if( me->query_temp("huohun/huo") )
	{
		message_vision("\n�����ӡ���Ѿ�����ҿ��ˣ�\n",me);
		return 1;
	}
	else
	{
		me->add_temp("huohun/yuanshen",1);
		me->set_temp("huohun/huo",1);
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