// Changed by sjmao  09-11-97
//changed by take 8-12-2001

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
int rank_me();
string expell_me(object me);
string ask_cfpl();

void create()
{
       set_name("��Ů", ({"long nu","gongzhu","long","princess"}));

	set("long","���ƹ����ˣ�������Ů����\n");
       set("gender", "Ů��");
       set("age", 20);
	set("int", 25+random(5));
        set("title", "���ƹ���");
       set("attitude", "peaceful");
        set("combat_exp", 350000);
  set("daoxing", 100000);

       set("rank_info/respect", "��������");
       set("class","dragon");
       set("per", 30);
       set("max_kee", 900);
       set("max_sen", 700);
       set("force", 800);
       set("max_force", 800);
       set("force_factor", 40);
       set("max_mana", 500);
       set("mana", 400);
       set("mana_factor", 30);
       set_skill("literate", 80);
       set_skill("unarmed", 100);
       set_skill("dodge", 120);
       set_skill("force", 80);
       set_skill("parry", 100);
       set_skill("fork", 80);
       set_skill("spells", 100);
        set_skill("seashentong", 80);
        set_skill("dragonfight", 80);
        set_skill("dragonforce", 80);
        set_skill("fengbo-cha", 100);
        set_skill("dragonstep", 120);
        map_skill("spells", "seashentong");
        map_skill("unarmed", "dragonfight");
        map_skill("force", "dragonforce");
        map_skill("fork", "fengbo-cha");
        map_skill("parry", "fengbo-cha");
        map_skill("dodge", "dragonstep");

        set("inquiry", ([ "�빬": (: expell_me :),
                "leave": (: expell_me :), 
		"ְλ": (: rank_me :),
		"�淨": (: ask_cfpl :),
				]) );

    create_family("��������", 2, "ˮ��");
	setup();

        carry_object("/d/obj/cloth/pinkskirt")->wear();
	carry_object("/d/sea/obj/yincha")->wield();
}
int rank_me()
{
        object me=this_player();
        int exp;
        exp=(int)me->query("combat_exp");
        if( me->query("title") == "��������")
		return notify_fail("���Ѿ����������ˣ�����Ҫʲôְλ��\n");
        if( (string)me->query("family/family_name") == "��������"){
                if( exp <= 100000 ){
                        me->set("title", HIR"��������"HIY"Ѳ��Ϻ��"NOR);
                 } else if(exp <= 1000000 ){
                        me->set("title", HIR"��������"HIY"Ѳ��ҹ��"NOR);
                  } else if(exp < 2000000 ){
                        me->set("title", HIR"��������"HIY"����ʹ"NOR);
                  } else if(exp < 3000000 ){
                        me->set("title", HIR"��������"HIY"�޵н���"NOR);
                } else {
                        me->set("title", HIR"��������"HIY"��������"NOR);
                }

                tell_object(me, "��Ů����˵���������"+me->query("title")+"��\n");
                tell_room(environment(me),
"��Ů��"+me->query("name")+"˵���������"+me->query("title")+"��\n", ({me, me}));
         CHANNEL_D->do_channel(me,"chat","�����豾�ŵ���"+me->query("name")+""+me->query("title")+"һְ�������λ�ɳ����������");
     me->save();  
        }
        return 1;
}
void attempt_apprentice(object ob)
{
        command("jump");
	command("say ���ֶ���һ������Ү��\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "dragon");
}
string expell_me(object me)
{
  me=this_player();
  if((string)me->query("family/family_name")=="��������")
    {
      message_vision("���ƹ����ѹ�������$N��������ֹ��\n", me);
      return ("��ȥ���Ҹ����ɡ�\n");
    }
  return ("ȥ���ʱ��˰ɣ�����ô��֪�����\n");
}

void die()
{
	object me,who,longjin;
    string whoid;
    me=this_object();
    if(me->query_temp("longjin_kill"))
	{
		  whoid=me->query_temp("longjin_kill");
    	  if (!present(whoid,environment()))
        	  return ::die();
	  	  who=present(whoid,environment());
          if((who->query("fangcun/panlong_hell_18")=="done")&&(who->query("fangcun/panlong_hell_longjin")=="begin")&&(environment()))
		{
			  longjin=new("/d/sea/obj/longjin");
			  longjin->move(me);
			  ::die();
			  return; 
		}
	}
      ::die();
}

string ask_cfpl()
{
	object me=this_player();
	if( me->query("betray/count") )
		return ("�����Ķ����޷����������ѧ��\n");
	if(me->query("family/family_name") != "��������" )
                return ("�㲻������������!!\n");
        if(me->query("cfpl_cant"))
      		return ("������ʲ��ʺ�ѧϰ�˷����ˣ�");
        if(me->query("cfpl_known")>1)
      		return ("�˷����˵Ŀھ��㶼�Ѿ�֪���˰���");
      	if(me->query("cfpl_lingwu"))
      		return ("��ȥ����������ɣ�");
      	if(me->query_skill("fork", 1) < 200 || me->query_skill("fengbo-cha", 1) < 200)
                return ("��Ĳ淨���𻹲�����\n");
        if(me->query_skill("hammer", 1) < 200 || me->query_skill("huntian-hammer", 1) < 200)
                return ("��Ĵ������𻹲�����\n");
        if(me->query_skill("unarmed", 1) < 200 || me->query_skill("dragonfight", 1) < 200)
                return ("����Ʒ����𻹲�����\n");
      	me->set_temp("cfpl/fork",1);
      	command("xixi");
      	return ("�粨ʮ����Ŀھ��Ϳ������������Ź������֮�ϣ���ȥ�Ҿ�ʦ���ʰɣ�");
}