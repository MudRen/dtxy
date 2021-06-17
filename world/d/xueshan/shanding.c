//sgzl
inherit ROOM;

void create ()
{
	set ("short", "雪山之巅");
	set ("long", @LONG

这里就是雪山最高地方，与其他地方不同的是，这里温暖
如春，四处开着各种奇花异草。
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