//jingwei.c
//created by vikee 2000.11

inherit NPC;
int fill_sea();
int do_sui(string arg);

void create()
{
 set_name("����", ({"jing wei","jing"}));
 set("long", "һֻ��˵�е�����ľ�����\n");
 set("combat_exp", 2000);
 set("attitude", "friendly");
 seteuid(getuid());
 set("attitude","heroism");
 set("chat_chance",20);
 set("chat_msg", ({
        "������̾������ãã������ʲôʱ�������ƽ��\n",
         "�������˲���ͷ�ĺ���һ���޾���ɵ����ӡ�"
         }));
         
 set("inquiry", ([
         "�": (: fill_sea :),
         "fill sea":(: fill_sea :),
         ]));
 setup();
}

int fill_sea()
{
        object who=this_player();
  if ( (who->query("combat_exp")<10000) || (who->query("daoxing") < 15000 ) || (who->query("live_forever")!=1 )
    {
    return "����Ǹ�Σ�յ��£���Ĺ���������ðȻ���ȥ�����ġ�\n";
    }
  else
    {
    who->set_temp("condition_ok", 1);
    return "��Ҫ��������Ը���һ��ȥ(sui jing wei).\n";
    }
    
}

void init()
{
  add_action("do_sui", "sui jing wei");
}

int do_sui(string arg)
{
object who=this_player();
who->command("follow jing wei");
}

