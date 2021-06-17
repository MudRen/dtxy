inherit __DIR__"l.c";
#include <ansi.h>
#define SDS_D "/d/newguai/npc/sdsd.c"

string *allroom = ({
        "/d/menggu/longjiao","/d/menggu/yuan11","/d/menggu/yuan12",     
        "/d/menggu/yuan13","/d/menggu/yuan21","/d/menggu/yuan22",     
        "/d/menggu/yuan23","/d/menggu/yuan31","/d/menggu/yuan32",     
        "/d/menggu/yuan33","/d/menggu/yuan41","/d/menggu/yuan42",     
        "/d/menggu/yuan43","/d/menggu/door1","/d/menggu/door2",      
        "/d/menggu/door3","/d/menggu/door4","/d/menggu/yading",     
        "/d/menggu/entrance",   
});
void create()
{
set_name("����", ({"ju long", "julong","long","dragon"}));
set("long","�ƽ������\n");
set("title",HIY"�ƽ�"NOR);
set("gender", "����");
set("age", 30);
set("family/family_name", "��������");
set("per", 20);
set("str", 30);
set("max_kee", 15000);
set("max_sen", 15000);
set("force", 10000);
set("max_force", 3000);
set("force_factor", 150);
set("max_mana", 2000);
set("mana", 4000);
set("mana_factor", 40);
set("combat_exp", 10000000);
set("daoxing", 10000000);
set_skill("huntian-hammer", 200);
set_skill("hammer", 200);
set_skill("unarmed", 300);
set_skill("dodge", 300);
set_skill("force", 300);
set_skill("parry", 500);
set_skill("fork", 200);
set_skill("spells", 200);
set_skill("seashentong", 200);
set_skill("dragonfight", 350);
set_skill("dragonforce", 300);
set_skill("fengbo-cha", 200);
set_skill("dragonstep", 400);
map_skill("hammer", "huntian-hammer");
map_skill("spells", "seashentong");
map_skill("unarmed", "dragonfight");
map_skill("force", "dragonforce");
map_skill("fork", "fengbo-cha");
map_skill("parry", "fengbo-cha");
map_skill("dodge", "dragonstep");
set_temp("apply/armor",400);
set_temp("apply/damage",35);
setup();
carry_object("/d/sea/obj/longpao")->wear();
}

void init ()
{
object ob = this_player();
object me = this_object();
if( living(ob) )
        call_out("greeting", 1, ob);
}

void greeting(object ob)
{
if ( !ob || environment(ob) != environment() ) 
        return;
if ( ob && interactive(ob))
        {
        message_vision ("$N���������ȵ����Ķ��������࣬�޷����죬���Ҵ�������԰��\n",this_object());
        ob->set_temp("julong_kill",1);
        }
}

int accept_fight (object ob)
{
kill_ob (ob);
return 1;
}

void kill_ob (object ob)
{
if ( !ob || !present(ob,environment()) )
       {
       if ( ob )  { 
             remove_killer(ob);
             ob->remove_killer(this_object());
             }
       remove_all_killer();
       return;
       }
set_temp("no_return",1);
set_temp("my_killer",ob);
::kill_ob(ob);
}

void unconcious()
{
die();
}

void die()
{
int i ,s,j;
object *alluser,room ,book,obj;
object *inv;
object ob = query_temp("last_damage_from");
alluser = filter_array(children(USER_OB),(: userp :));  
s=sizeof(alluser);

  if( !ob ) { ::die();return;}
        
if ( random(30)==0 && (time()-(int)ob->query("mark/last_jinlongget")>3*24*3600 ) 
  && ob->query("combat_exp") > 3000000 )
        {
        //book = new("/d/obj/book/wangqing");       
        //if ( book && book->move(ob) )
                {
                ob->set_skill("wangqing-jue",1);
                ob->set("mark/jinlong", "wangqing");
                message("chat",HIY"\n��С����Ϣ��"+HIM"��˵"+ob->query("name")+"������"HIR"���������"HIM"���壡��\n\n"NOR,users());
                log_file("tulong",sprintf("%s(%s) get wangqing on %s\n",ob->name(1), ob->query("id") ,ctime(time()) ) );
                }
        }
else if ( random(20) < 0 && (time()-(int)ob->query("mark/last_jinlongget")> 3*24*3600) 
        && ob->query("combat_exp") > 3000000)
        {
        //book = new("/d/obj/book/jinlongji");       
        //if ( book->move(ob) )
                {
                message("chat",HIY"\n��С����Ϣ��"+HIM"��˵"+ob->query("name")+"�õ���"HIR"������ѪӰ����"HIM"�ؼ�����\n\n"NOR,users());
                ob->set_skill("jinlong-strike",1);
                ob->set("mark/jinlong", "jinlongji");
                log_file("tulong",sprintf("%s(%s) get jinlong on %s\n",ob->name(1), ob->query("id") ,ctime(time()) ) );
                }
        }
else if (random(15) < 0 && (time()-(int)ob->query("mark/last_jinlongget")> 3*24*3600) 
         && ob->query("combat_exp") > 3000000)
        {
        //book = new("/d/obj/book/jinwu");       
        //if ( book->move(ob) )
                {
                message("chat",HIY"\n��С����Ϣ��"+HIM"��˵"+ob->query("name")+"�õ���"HIR"�����ڵ�����"HIM"���ף���\n\n"NOR,users());
                ob->set_skill("jinwu-blade",1);
                ob->set("mark/jinlong", "jinwu");
                log_file("tulong",sprintf("%s(%s) get jinwu on %s\n",ob->name(1), ob->query("id") ,ctime(time()) ) );
                }
        }
else    {
        ob->add("g_balance",250000);
		message("chat",HIY"\n��С����Ϣ��"+HIM"��˵"+ob->query("name")+"����˴�����Ʊ����\n\n"NOR,users());
        }
message_vision(HIG"$N�۵ô򼸸��������¶������ڼ�����ʧ�������......\n"NOR,this_object());
message_vision(HIG"��ﳤ����һ������Ѹ���뿪������ֲ������ѡ�\n"NOR,this_object());
message_vision(HIR"�������ѵض�ɽҡ......\n"NOR,this_object());
message("chat",HIY"\n��С����Ϣ��"+HIY"��˵"+ob->query("name")+"����һ�����´�����԰�������˻ƽ��������\n\n"NOR,users());
ob->set("mark/last_jinlongget",time());
if(!( room = find_object("/d/menggu/longjiao")) )
        room = load_object("/d/menggu/longjiao");
room->set("push","");
room->set("in",1);
room->set("push_id","");
for (i=0;i<s;i++) 
        {
        obj=alluser[i];
        if (obj->query_temp("julong_kill") == 1 || obj->query_temp("julong_ask") == 1)
                {
                obj->move("/d/menggu/damo");
                obj->delete_temp("julong_kill");
                obj->delete_temp("julong_ask");
                }
        }
     destruct(this_object());
}
/*
varargs int receive_damage(string type, int damage, object who)
{
object me = this_object();
if ( !who || (who && who!=me) && !me->is_busy() && random(10)!=9 && damage<100 )
        return ::receive_damage(type,damage,who);
message_vision("\n$N��β��һɨ��$nֻ��һ��ǿ����������������$p���һ���£��е�������......\n"NOR,me,who);
damage = 1+random(damage/2);
who->receive_wound(type,damage/5,me);
COMBAT_D->report_status(who,damage/5);
return ::receive_damage(type,damage,who);
}
*/

