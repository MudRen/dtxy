//changan city
// Cracked by 凌惊雪 1-3-2003

inherit ROOM;
#include <ansi.h>

void create ()
{
        set ("short", "龙窖");
        set ("long", 
HIY"这儿就是龙窖了，眼前一片金黄色，地上有许多巨龙掠夺来\n的财宝。\n\n"NOR
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
        //第4个人push的时候,hero==3,而不是4
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
    write("这个地方没法使用"+arg+"。\n");
    return 1;
}

/*
int do_shout( string arg )
{
  object *inv;
  object ob;
  int i;
  object room;

  if( arg != "屠龙" ) return 0;
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

