//changan city
// Cracked by �辪ѩ 1-3-2003

inherit ROOM;
#include <ansi.h>

void create ()
{
        set ("short", "����԰");
        set ("long", @LONG
������ǹ��������԰����Χ��ɭɭ�ģ�ֻ���ĸ��ں����Ķ��ڣ�
Ҳ��֪ͨ��δ���

LONG);
	set("objects", ([ /* sizeof() == 1 */
        __DIR__"npc/shouwei.c" : 1,
]));

        set("exits", 
        ([ //sizeof() == 4
                "west" : __DIR__"yuan32",
        ]));
        setup();
}
int valid_leave(object me, string dir)
{
	if ( present("wangyou shouwei") )
		return notify_fail("����������ס�����ȥ·��\n");
    	return ::valid_leave(me, dir);
}
void init()
{
  add_action("do_cast",({"cast"}));
}
int do_cast(string arg) {
    string *banned_cast=({"chuqiao","qiankun","jieti"});
    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2) ;
    if(member_array(arg,banned_cast)==-1) return 0;
    write("����ط�û��ʹ��"+arg+"��\n");
    return 1;
}

