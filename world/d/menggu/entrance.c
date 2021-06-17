// Cracked by 凌惊雪 3-18-2003
//为防止马甲破坏，又不清楚原系统的设定，所以新加个data
// snowtu

inherit ROOM;
#include <ansi.h>

string *add_arr(string *ids,string id);
static int flag = 1;

void create ()
{
set ("short", "忘忧园入口");
set ("long", @LONG
这儿就是关外的忘忧园。周围阴森森的，只有四个黑乎乎的洞口，
也不知通向何处。

LONG);
set("objects", ([
        __DIR__"npc/shouwei.c" : 5,
]));
set("in",1);
set("exits", ([ 
        "1" : __DIR__"yuan11",
        "2" : __DIR__"yuan21",
        "3" : __DIR__"yuan31",
        "4" : __DIR__"yuan41",
]));
setup();
}

void reset()
{
if ( time()<query_temp("last_enter_time")+3600 )
         return;
if ( random(10)==0 ) message("channel:rumor",HIM"\n【小道消息】某人：听说忘忧园的入口好似开了。\n"NOR,users());
delete_temp("last_enter_time");
delete_temp("enter");
set("in",1);
::reset();
}

void init()
{
add_action("do_cast",({"cast"}));
}

int valid_leave(object me, string dir)
{
int i;
string name,*ids;
object *inv;
inv = all_inventory(me);
for(i=0; i<sizeof(inv); i++)
        {   
        if (inv[i]->is_character() )
                return 1;
        }
if ( present("wangyou shouwei") )
        return notify_fail("守卫伸手拦住了你的去路。\n");
if ( this_object()->query("in")>8 )
        {
        ids =   query_temp("enter");
        name = "";
        i = sizeof(ids);
        while(i--)
                {
                if ( ids[i] && stringp(ids[i]) )
                        name+= ids[i];
                if ( i>0 )  name+= "、";
                else    name+= " ";     
                }
        if ( time()<query_temp("last_enter_time")+3600 )
                return notify_fail("好象没什么必要再进去了,"+name+"他们已经进去把龙杀完了。\n");
        else return notify_fail("好象出问题了,现在龙应该已经出来了,联系wiz吧。\n");
        }
//added By Snowtu       
ids = query_temp("enter");
ids = add_arr(ids,me->query("id"));
set_temp("enter",ids);
//(*)End

add("in",1);
set_temp("last_enter_time",time());
if ( query("in")>=8 && flag ) 
       {
       message("channel:rumor",HIM"\n【小道消息】某人：听说杀龙的队伍已全部进入了忘忧园。\n"NOR,users());
       flag = 0;
       }
return ::valid_leave(me, dir);
}

int do_cast(string arg) 
{
string *banned_cast=({"chuqiao","qiankun","jieti"});
if ( !arg ) return 0;
while(sscanf(arg,"%s %*s",arg)==2) ;
if ( member_array(arg,banned_cast)==-1 ) 
        return 0;
write("这个地方没法使用"+arg+"。\n");
return 1;
}

//Added By Snowtu
string *add_arr(string *ob,string obj)
{
int i;
string *oo = ({});      
if ( !obj || !stringp(obj) )
        return ob;
if ( arrayp(ob) && member_array(obj,ob)!=-1 )
        return ob;
i = sizeof(ob);         
while(i--)
        if ( ob[i] && stringp(ob[i]) )  
                oo+= ({ob[i]});
oo+= ({obj});
message("channel:sys",WHT"〖"NOR HIB"屠龙"NOR WHT"〗"+obj+WHT"进入忘忧园>>>>>>>>>>>>>首次进入,记录在案.\n"NOR,users());
return oo;
}       



