inherit NPC;
#include <ansi.h>
#include <obstacle.h>
int give_gift();
int give_sword();
int give_blade();
int give_tianfu();
int give_tlbb();
int give_dan();
int give_zichuang();
int give_quzhu();
int telling1 (object who);
int telling2 (object who);
string name = "��";
void create()
{
	set_name("����", ({"qujing","qu jing"}));
   	set ("long", @LONG
�ݹ�˵�ˣ�ȡ��̫�鷳�ˣ������Լ�ȡ���ľ������Ұɡ�
LONG);
       	set("gender", "����");
	set("title",HIB"����"NOR);
        set("age", 21);
        set("per", 40);
       	set("attitude", "peaceful");
       	set("shen_type", 1);
	set("inquiry", ([
	        		"qujing":(:give_gift:),
//	        		"sword":(:give_sword:),
	        		"tianfu":(:give_tianfu:),
	        		"tlbb":(:give_tlbb:),
//	        		"zichuang":(:give_zichuang:),
	        		"hyd":(:give_dan:),
			]));
        setup();
}

void init()
{
        object ob;
        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object ob)
{
  	command("say ��͵���������Ұɡ�");
}
int give_gift()
{
	object player = this_player();
	if( player->query("daoxing") + player->query("combat_exp") < 100000 )
	{
		command("say �����Ϊ����������һ����֪���Ҹ��㿪�����ˣ������Ȼؼ������ɣ�\n");
		return 1;	
	}
		//return notify_fail("�����Ϊ����������һ����֪���Ҹ��㿪�����ˣ������Ȼؼ������ɣ�\n");
	telling1(player);
	telling2(player);
	return 1;	
}
int give_tianfu()
{
	object player = this_player();
	//player->set("kar",30);
	player->set("int",50);
	//player->set("cps",40);
	//player->set("cor",40);
	//player->set("str",30);
	//player->set("con",30);
	//player->set("per",30);
	//player->set("spi",30);
	return 1;
}
int give_sword()
{
	object player = this_player();
	object sword = new("/d/npc/obj/dragonxiao");
	sword->move(player);
	return 1;
}
int give_blade()
{
	object player = this_player();
	object blade = new("/u/kugu/obj/fengdao");
	blade->move(player);
	return 1;
}
int telling1 (object who)
{
  int size = sizeof(obstacles);
  string *names = keys(obstacles);
  string *strs = allocate (size);
  int nb = 0;
  int i;

  for (i = 0; i < size; i++)
  {
    strs[i] = "none";
  }

  for (i = 0; i < size; i++)
  {
    if (who->query("obstacle/"+names[i])=="done")
    {
      strs[nb] = obstacles[names[i]];
      nb++;
    }
  }

  if (nb == 0)
  {
    write (name+"��δ������ȡ�澭��\n");
  }
  else
  {
    write (name+"������ȡ�澭�ѹ���"+chinese_number(nb)+"�أ�\n");
    who->set("obstacle/number",nb);
    strs = (string *)sort_array (strs, 1);
    for (i = 0; i < nb; i++)
    {
      write ("    "+strs[i]+"\n");
    }
  }
  return 1;
}

int telling2 (object who)
{
  int size = sizeof(obstacles);
  string *names = keys(obstacles);
  string *strs = allocate (size);
  int nb = 0;
  int i;

  for (i = 0; i < size; i++)
  {
    strs[i] = "none";
  }

  for (i = 0; i < size; i++)
  {
    if (who->query("obstacle/"+names[i])!="done")
    {
      who->set("obstacle/"+names[i],"done");
      if( who->query("obstacle/number") < sizeof(obstacles) ) who->add("obstacle/number",1);
      strs[nb] = obstacles[names[i]] + " -- ok!";
      nb++;
    }
  }

  if (nb == 0)
  {
    write (name+"������ȡ�澭�����������е��ѹء�\n");
    command("say �Լ����㶨�ˣ��������Ҹ��𣿣�");
    command("kick "+ who->query("id"));
  }
  else
  {
    write (name+"������ȡ�澭�����"+chinese_number(nb)+"�أ�\n");
    strs = (string *)sort_array (strs, 1);
    for (i = 0; i < nb; i++)
    {
      write ("    "+strs[i]+"\n");
    }
  }
  return 1;
}

int give_tlbb()
{
	object player = this_player();
	player->set("babu/shendian","done");
	return 1;
}

int give_dan()
{
	object player = this_player();
	object blade = new("/d/obj/drug/huanyang");
	blade->move(player);
	return 1;
}

int give_zichuang()
{
	object player = this_player();
	player->set("wuxing_known",3);
	return 1;
}

int give_quzhu()
{
	object player = this_player();
	if( player->query("id") != "zliu" )
		return 1;
	player->set("quzhu_known",3);
	return 1;
}
