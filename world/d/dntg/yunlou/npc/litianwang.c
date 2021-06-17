//modified by vikee for xlqy-zq station
//2000-12-2 1:34

inherit NPC;
#include <ansi.h>
#include <obstacle.h>

string *list=({"yg-putuo","yg-moon","yg-wzg","yg-shushan","yg-hyd",
    "yg-fangcun","yg-hell","yg-jjf","yg-pansi","yg-kunlun",
        "yg-dragon", "yg-xueshan","yg-sanxian",
	"yg-wudidong",
	});

int work_me();
int cancel_me();
int delete_ask(object me);
 
void create()
{
 
	set_name("�", ({ "li jing", "jing", "li" }) );
	set("gender", "����" );
	set("long", "�����������������Ԫ˧������ʮ������콫�������ޱߡ�\n");
	set("age",40);
	set("title", "��������");
	set("str", 40);
	set("int", 30);
	set("con", 30);
	set("spi", 30);
	set("per", 30);
	set("class", "xian");
	set("attitude", "heroism");
	set("combat_exp", 4500000);
	set("daoxing", 8000000);
	set("max_kee", 4000);
	set("max_sen", 4000);
	set("force",9000);
	set("max_force",5000);
	set("force_factor", 500);
	set("mana", 9000);
	set("max_mana", 9000);
	set("mana_factor", 550);

	set("eff_dx", 600000);
	set("nkgain", 600);

	set_skill("spells", 280);
        set_skill("dao", 250);
        set_skill("unarmed", 250);
        set_skill("yinfeng-zhua", 250);
        set_skill("dodge", 280);
        set_skill("blade", 280);
        set_skill("kugu-blade", 280);
        set_skill("yaofa", 300);
        set_skill("lingfu-steps", 280);
        set_skill("parry", 280);
        set_skill("force", 280);
        set_skill("huntian-qigong", 280);
        set_skill("blade", 280);
        set_skill("sword", 300);
        set_skill("qixiu-jian", 280);
        map_skill("spells", "dao");
        map_skill("unarmed", "yinfeng-zhua");
        map_skill("parry", "huoyun-qiang");
        map_skill("sword", "qixiu-jian");
        map_skill("dodge", "lingfu-steps");
        map_skill("force", "huntian-qigong");
	
        create_family("�ݿ�ɽ�޵׶�", 1, "����");
	set("chat_chance",1);
	set("chat_msg", ({
		    name()+"˵������λ���ɿ�Ըȥ�½�������\n",
		    }));

        seteuid(getuid());

	set("inquiry", ([
	"mieyao": (: work_me :),
	"kill": (: work_me :),
	"����": (: work_me :),
	"����": (: cancel_me :),
	"fangqi": (: cancel_me :),
	"cancel": (: cancel_me :),
	]));

	setup();
	carry_object("/d/obj/fabao/huangjin-baota");
	carry_object("/d/obj/armor/jinjia")->wear();
	carry_object("/d/sky/obj/zhanyaojian")->wield();
}
//this funtion is modified by vikee 2000-11-20 1:32
int cancel_me()
{	object ghost,me=this_player();
//this modi by cnd delete here if for bug
	if(!me->query("mieyao/time_start")||
	   me->query("mieyao/time_start")+1800<time() ||
	   me->query("mieyao/time_start")>time() ||
	   me->query("mieyao/done")||
	   !me->query_temp("mieyao/ob"))
	   
	{
	   command("bite");
	   command("say ��û����ɱ��������ʲô���֣�\n");
        me->delete_temp("mieyao/ob");
         me->delete_temp("mieyao/name");
         me->set_temp("mieyao/level",1);
         me->set("mieyao/done",1);
	   return 1;
       }
	ghost=me->query_temp("mieyao/ob");
	if (!living(ghost))
	{
	   command("say "+ghost->query("name")+"��������Ѿ�����!\n");
	   return 1;
        }
	me->delete_temp("mieyao/ob");
// ɾ����������
	me->delete_temp("mieyao/name");
	me->delete_temp("mieyao/time_start");
	//��������������,��ǰ��level�ӵ�һ����ʼ.
	me->set_temp("mieyao/level",1);
	command("shrug");
	command("say ���Ȼ�����շ�"+ghost->query("name")+", ֻ������ȥ�ˡ�\n");
	me->set("mieyao/done",1);

	destruct(ghost);
	return 1;
}
 
int work_me()
{
	object ghost, me;
	int t, lvl;
	int size1 = sizeof(obstacles);
	me=this_player();
	//for first time.
	/*if (me->query("obstacle/number") >= size1){
		message_vision("$N˵"+
			"����λ"+RANK_D->query_respect(me)
			+"��ȡ���澭���ó�����,�뵽�ҷ�������������ħ������\n",
			this_object(), me);
		return 1;
	    }*/
	
	if (me->query("daoxing")<100000) 
	{
		message_vision("$N˵"+
			"����λ"+RANK_D->query_respect(me)
			+"���в��㣬�����ȵ��½���������\n",
			this_object(), me);
			return 1;
	}
	if(!me->query("mieyao")) {
		call_out("start_job", 1, me);
		return 1;
	}
	
 if (me->query_temp("pkgame")) return notify_fail("��������ȣ�\n");
	if( (t=(int)me->query("mieyao/time_start")) &&
		!me->query("mieyao/done")) {

	    if(t<=time() &&
		    time()<t+1800) {
		//command("heng");
		//command(
 		//  "say �Ϸ�������ȥ����"+me->query("mieyao/name")
		//  +"��\n");
		message_vision(CYN"$N��������Щ�����ˣ������������һ����\n"NOR,this_object());
		message_vision(CYN"$N˵�����Ϸ�������ȥ����"+me->query("mieyao/name")+"��\n"NOR,this_object());
		return 1;
	    }
	    // here is modified by vikee for the #9 ask li about kill 's bug
	    // or the #8 {u;ask li about kill;d}'s bug,
	    // set a flag "mieyao/level_change" to judge the monster level.
	    
	    if(!me->query_temp("mieyao/level_changed")) {
		lvl=me->query_temp("mieyao/level");
		if(lvl>0) lvl--;
		me->set_temp("mieyao/level",lvl);
		me->set_temp("mieyao/level_changed",1);
	    }
	    // allow ask again.
	} else { // job done
	    if(!wizardp(me) && t<=time() &&
		    time()<t+90) {
		message_vision("$N������������һ����˵"+
			"����λ"+RANK_D->query_respect(me)
			+",��ħ�ѳ���,������ȥЪϢ��\n",
			this_object(), me);
		return 1;
	    }
	    // succeed, increase lvl.
	    if(!me->query_temp("mieyao/level_changed")) {
		lvl=me->query_temp("mieyao/level");
		if(lvl<11) lvl++; // total 10 levels: 0, ..., 9
		else
		    lvl=1; // reach the top level, reduce difficulty.
		me->set_temp("mieyao/level",lvl);
		me->set_temp("mieyao/level_changed",1);
	    }
	}
	me->delete("mieyao/time_start");
	call_out("start_job", 1, me);
	return 1;
}
int start_job(object me)
{	string where;
	object ghost;
	int lvl;
        string g_title;
 
	if(environment(me)!=environment()) return 1;
	if(me->query("mieyao/time_start")) return 1;
	me->delete("mieyao/done");
	me->set_temp("mieyao/level_changed",0);

	// determine levels.
	// use temp mark, if quit, then start over.
	lvl=me->query_temp("mieyao/level");
	
        ghost = new(__DIR__+list[random(sizeof(list))]);
        where=ghost->invocation(me, lvl);
        g_title=ghost->query("title")+" ";
	message_vision("$N���������������½�һ�Σ�\n",this_object());
	message_vision("$N��$n˵��������"+g_title+where+"Ϊ��������"
		+"����ȥ������\n"
		,this_object(),me);
	me->set("mieyao/time_start", time());
	me->set("mieyao/name",ghost->query("name"));
	me->set_temp("mieyao/ob",ghost);
	return 1;
}

int delete_ask(object me)
{
        me->delete_temp("asked/lijing");
        return 1;
}


void attempt_apprentice(object ob)
{

if (ob->query("obstacle/number") < 26) {
 command("say ��λ" + RANK_D->query_respect(ob) + "����Ϊʦ��Ҫ��������ȡ
�����ѣ�\n");
 command("sigh");
 return;
}

  if ((string)ob->query("family/family_name")=="�ݿ�ɽ�޵׶�") {
       if(ob->query("combat_exp") > 1000000 && ob->query("daoxing") > 1000000) {
	   command("ok");
	   command("say "+RANK_D->query_respect(ob)+"�ð�,�������Ҷ��ӵķ���,�Ҿ��������ˡ�");
           command("recruit "+ob->query("id"));
  	  }
  } else {
  	command("say �Ҳ���ʶ�㡣");
	command("sorry");
  }	
 }
  
int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "yaomo");
                ob->set("title", HIR"Ѫ����"NOR);
}

/*int prevent_learn(object me, string skill)
{
  int myyaofa=me->query_skill("yaofa",1);

  if (skill == "dao") {
	if(myyaofa!=0) {
		command("sigh");
		command("say "+RANK_D->query_respect(me)+"����̫�أ�����ѧ�����ɷ���");
		return 1;
	}
  }
  return 0;
}

*/

