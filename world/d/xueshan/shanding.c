//sgzl
inherit ROOM;

void create ()
{
	set ("short", "ѩɽ֮��");
	set ("long", @LONG

�������ѩɽ��ߵط����������ط���ͬ���ǣ�������ů
�紺���Ĵ����Ÿ����滨��ݡ�
LONG);


	set("exits", 
	([ //sizeof() == 4
                "down" : __DIR__"no4-enter",
	]));
	
	set("objects", 
	([
		__DIR__"npc/phoenix" : 1,
	]));

	setup();
}

int valid_leave(object me, string dir)
{
  	if( dir == "down" ) me->delete_temp("meet");
  	return ::valid_leave(me,dir);
}