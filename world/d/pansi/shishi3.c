// shishi3.c
// by lestat/2000.1.31

inherit ROOM;
#include <ansi.h>;
void create()
{
	set("short", HIG"��ң��"NOR);
	set("long", @LONG
������һ�������ʯ�ң���֮������κ�һ������������������һ����
��������ľ�Ƴɵ����(shelf),���������ȴ�յ�������һ����Ҳû�С�
���л���һ�ź�����(bed)��
LONG );
	set("exits", ([
		"south" : __DIR__"shidong",
	]));
	set("item_desc", ([
		"bed"   : "һ��ǧ�꺮����,����������ƶ�һ������\n",
		"shelf" : "���������һ��С�����������֮����������֮�磬�����������Ϊ��ң����\n",
	]));
		set("objects",([
		__DIR__"obj/guo" : 3,
		__DIR__"npc/jikao" : 1,
	]));
//	set("book1_count",1);
	set("no_clean_up", 0);
	setup();
}

int do_move(string arg)
{
	object me;

	me=this_player();
	if(!arg || arg!="bed") return 0;
	message_vision("$N������С���ƿ����������澹Ȼ��һ������ͨ����\n",me);
	me->move(__DIR__"midao1");
	tell_object(me,"������һ���¡¡���������㶨��һ�����Լ��Ѿ�����������ͨ�����ˡ�\n");
	return 1; 
}

void init()
{
        add_action("do_bed", "gosleep");
        add_action("do_bed", "gobed", );
        add_action("do_bed", "bed");
		add_action("do_move","move");
		add_action("do_strike","strike");
}

int do_bed()
{       object me;
        me=this_player();
        message_vision(HIY "$N�ƿ�ɴ�ʣ�׼���ϴ��ˡ�\n\n" NOR, me);
        me->move(__DIR__"bed");
            message_vision(HIY "\nɴ������һ����$N���˽�����\n" NOR, me);
                return 1;
}
int do_strike(string arg)
{
        object me = this_player();
		object sha;
	if( me->query("lunhui_zhuanshi") < 3 )
		return notify_fail("�㻹û��ת�����Σ�����ѧϰ���Ž�����\n");
if( me->query("rulaitask/get") )
             {message_vision(CYN"\n�����������������й��򰡡�\n"NOR,me);
              return 1;
             }
if( me->query_temp("pkgame") )
    return notify_fail("�㻹�ǵȱ��������������ɡ�\n");
             
        if(!arg || arg!="shelf") return 0;
        message_vision("$N���ſ��ţ���Ȼ�͵�һ������ܴ�ȥ�������ܡ������������������˼�����\n",me);
	
//     if (random(100) > 1 && this_player()->query("mark/daya-jian"))
if (random(100) > 97 && this_player()->query("mark/daya-jian") && this_player()->query("combat_exp") > 6600000 )
	{
      if (this_player()->query("mark/dayagett"))
	  {
        message_vision("��Ȼ��$N����һ�������ٺٵؼ�Ц����\n",me);
        message_vision("���ţ���֪���������һ֧������������$N��\n",me);
        me->die();
	  }
	  else {
		sha = new (__DIR__"obj/daya-book");
     	this_player()->set("mark/dayagett", 1);
		sha->move(me); 
		me->move(__DIR__"shishi3");
        message("channel:rumor", MAG"���������š�ĳ�ˣ�"+this_player()->query("name")+"����˿���õ��˴��ŹŽ�������\n"NOR, users());
		tell_object(me, "ͻȻֻ��һ�����������������Ʈ������������Ͻ����������ڻ��\n");
	}
	}
	  else { 
		message_vision("��Ȼ��$N����һ�������ٺٵؼ�Ц����\n",me);
        message_vision("���ţ���֪���������һ֧������������$N��\n",me);
		me->die();
//				tell_object(me, "ͻȻֻ��һ�����������������Ʈ������������Ͻ����������ڻ��\n");

	  }

        return 1; 
}
