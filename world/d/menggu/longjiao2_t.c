//changan city
// Cracked by �辪ѩ 1-3-2003

inherit ROOM;
#include <ansi.h>

void create ()
{
        set ("short", "����");
        set ("long", 
HIY"������������ˣ���ǰһƬ���ɫ���������������Ӷ���\n�ĲƱ���\n\n"NOR
);
	set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/long" : 1,
]));
	set("push","");
	set("push_id","");
        setup();
}
void init() {
  add_action("do_cast",({"cast"}));
}
int do_cast(string arg) {
    string *banned_cast=({"chuqiao","qiankun","jieti"});
    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2) ;    if(member_array(arg,banned_cast)==-1) return 0;
    write("����ط�û��ʹ��"+arg+"��\n");
    return 1;
}


