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
//        set("objects", ([ /* sizeof() == 1 */        __DIR__"npc/long.c" : 1,]));

        set("hero",0);
	set("push","");
	set("push_id","");
        setup();
}
void init() {
    object ob;
  add_action("do_cast",({"cast"}));
//    add_action("do_shout","shout");
        if( this_object()->query("hero") == 3 )
        //��4����push��ʱ��,hero==3,������4
        {
                this_object()->set("hero",0);
                ob = new("/d/menggu/npc/long");
                ob->move(this_object());
        }
}
int do_cast(string arg) {
    string *banned_cast=({"chuqiao","qiankun","jieti"});
    if(!arg) return 0;
    while(sscanf(arg,"%s %*s",arg)==2) ;    if(member_array(arg,banned_cast)==-1) return 0;
    write("����ط�û��ʹ��"+arg+"��\n");
    return 1;
}

/*
int do_shout( string arg )
{
  object *inv;
  object ob;
  int i;
  object room;

  if( arg != "����" ) return 0;
  room = this_object();
  if( room->query("push") == "" )
    return 0;

  inv = all_inventory(this_object());
  for( i=0; i<sizeof(inv); i++ )
  {
  }
  if( sizeof(inv) != 4 ) return 0;
  ob = new("/d/menggu/npc/long");
  ob->move(this_object());
  room->set("push","");
  return 0;
  
}

*/

