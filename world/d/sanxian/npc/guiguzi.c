//������ɢ�ɡ�lestat 2001/8
// �����

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string expell_me(object me);
string ask_icefire();
void create()
{
       set_name("�����", ({ "gui guzi", "guzi", "gui" }));
//        set("title","");
        set("long", 
"��˵�е����ɣ���ͷ�׷������ˣ����۾�������\n");

        set("gender", "����");
        set("age", 665);
        set("attitude", "peaceful");
        set("str", 100);
        set("int", 40);
        set("con", 30);
        set("per", 20);
        set("class","sanxian");
        
        set("kee", 4000);
        set("max_kee", 4000);
        set("sen", 3000);
        set("max_sen", 3000);
        set("force", 15000);
        set("max_force", 8000);
        set("max_mana",8000);
        set("mana",12000);
        set("force_factor", 500);
        set("mana_factor", 500);
        set("combat_exp", 100000000);
        set("daoxing", 100000000);

        set_skill("spells",300);
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("sword", 300);   
        set_skill("binfen-steps", 300);        
        set_skill("literate", 300);
        set_skill("ice_fire_zhang", 300);
        set_skill("unarmed", 300);
        set_skill("whip", 300);
        set_skill("butian-force", 300);
        set_skill("mysticism", 300);
        set_skill("wuwei-fuchen", 300);
        set_skill("spysword", 300);        
        map_skill("dodge", "binfen-steps");        
        map_skill("parry", "spysword");
        map_skill("sword", "spysword");
        map_skill("force", "butian-force");
        map_skill("spells", "mysticism");
        map_skill("whip", "wuwei-fuchen");
         map_skill("unarmed", "ice_fire_zhang");
        set("inquiry",([
      		"�����"    : (: ask_icefire :),
      			]));


        create_family("����ɢ��", 1, " ��");
	set("icefire_known",2);
	set("old_flag/jiandao",10);
        set("chat_chance_combat", 90);
	   set("chat_msg_combat", 
	   ({
	     (: perform_action, "unarmed","icefire" :),
	     (: perform_action, "sword","bishou" :),
	     (: perform_action, "sword","dunnoname" :),
	     (: perform_action, "sword","dunnotruth" :),
	    }) );
   add_temp("apply/damage", 135);
   add_temp("apply/attack", 135);
   add_temp("apply/dodge", 135);
   add_temp("apply/spells", 100);
   add_temp("apply/armor", 150);
   add_temp("apply/armor_vs_force",250);
   add_temp("apply/armor_vs_spells",250);
   
        setup();
        carry_object("/d/obj/weapon/sword/qinghong")->wield();
        carry_object("/d/obj/cloth/choupao")->wear();
}
int is_ghost() { return 1; }

void attempt_apprentice(object ob)
{
   if ( (string)ob->query("family/family_name")=="����ɢ��") {
if (ob->query("obstacle/number") < 26) {
command("say ��λ" + RANK_D->query_respect(ob) + "����Ϊʦ��Ҫ��������ȡ�����ѣ�\n");
 command("sigh");
 return;
}
  if (((int)ob->query("daoxing") < 1000000 )) {
   command("say " + RANK_D->query_respect(ob) +
"�ĵ��в��������Щ��ѧ�ط�������������\n");
   return;
   }
        command("pat "+ob->query("id"));
        command("recruit " + ob->query("id") );
        return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +
"�Ҳ���ʶ��ɡ�\n");
        return;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
   ob->set("class", "sanxian");
   ob->set("title",HIB"����Ӵ���"NOR);
   }

string ask_icefire()
{
	object me = this_player();
	if( me->query("betray/count") )
		return ("�����Ķ����޷����������\n");
	if(me->query("family/family_name") != "����ɢ��" )
                return ("�㲻����ɢ�ɵ���!!\n");
        if(me->query("icefire_known") > 1 )
      		return ("������Ŀھ��㶼�Ѿ�֪���˰���");
      	if(me->query("icefire_cant"))
      		return ("���޷�������ߵı������");
      	if( me->query_skill("literate",1) < 200 )
		return ("�����ѧʶ����������������");
	if( me->query_skill("ice_fire_zhang",1) < 200 )
		return ("������Ʒ�����������������");
	if( me->query_skill("butian-force",1) < 200 )
		return ("������ڹ�����������������");	
	if( me->query_skill("wuwei-fuchen",1) < 200 )
		return ("�����޷�����������������");	
      	command("addoil");
      	if( me->query("icefire") )
      	{
      		command("say �ҵ���ĺ���Ϣ��");
      	}
      	else if( !me->query("icefire_known") )
      	{
		me->set("icefire/ice",1);
		me->set("icefire/fire",1);
		command("say Ҫ����������Ҫ���������������ķ��������������ǵ��ͺ�������");
		command("say ���ѻ�߶���İ�����ܴ����ȥ��������xiulian���ɡ�");
	}
	else
	{
		me->set("icefire/ice",3);
		me->set("icefire/fire",3);
		command("say Ҫ���������ı�������������ͬʱ��ת���������ķ���");
		command("say ���ѻ�߶���İ�����ܴ����ȥ��������xiulian���ɡ�");
	}
	return ("һ�ж��С�ģ�");
}



