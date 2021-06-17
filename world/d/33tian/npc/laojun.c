// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
//puti.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
string ask_wuxing();
void create()
{
       set_name("̫���Ͼ�", ({"taishang laojun","laojun"}));
       set("long", "�쳾һЦǣ��ţ,���˽����Ҷ���.\n");
       set("title", MAG"��������"NOR);
       set("gender", "����");
       set("age", 100);
   set("class", "taoist");
       set("attitude", "friendly");
       set("shen_type", 1);
       create_family("��ׯ��", 1, "��ʦ");
   set("rank_info/respect", "�Ͼ�");
   set_skill("unarmed", 300);
   set_skill("wuxing-quan", 300);
   set_skill("dodge", 300);
   set_skill("baguazhen", 300);
   set_skill("parry", 300);
   set_skill("sword", 300);
   set_skill("sanqing-jian", 300);
   set_skill("staff", 300);
   set_skill("fumo-zhang", 300);
   set_skill("hammer", 300);
   set_skill("kaishan-chui", 300);
   set_skill("blade", 300);
   set_skill("yange-blade", 300);
   set_skill("force", 300);   
   set_skill("zhenyuan-force", 300);
   set_skill("literate", 300);
   set_skill("spells", 300);
   set_skill("taiyi", 300);
   map_skill("spells", "taiyi");
   map_skill("force", "zhenyuan-force");
   map_skill("unarmed", "wuxing-quan");
   map_skill("sword", "sanqing-jian");
   map_skill("parry", "sanqing-jian");
   map_skill("dodge", "baguazhen");
   map_skill("staff", "fumo-zhang");
   map_skill("blade", "yange-blade");
   map_skill("hammer", "kaishan-chui");
   set("inquiry",([
      "����": (: ask_wuxing :),
      ]));
  set("str",100);
  set("per",100);
  set("max_kee", 10000);
  set("max_gin", 10000);
  set("max_sen", 10000);
  set("force", 10000);
  set("max_force", 10000);
  set("force_factor", 500);
  set("max_mana", 10000);
  set("mana", 10000);
  set("mana_factor", 500);
  set("combat_exp", 10000000);
  set("daoxing", 10000000);

   set("spell_qiankun_on", 1); //to use cast qiankun, must set this.
   set("faith",1000);
   set("wuxing_known",3);
   set("chat_chance_combat", 90);
   set("chat_msg_combat", 
   ({
     (: cast_spell, "qiankun" :),
     (: perform_action, "unarmed","wuxing" :),
     (: perform_action, "sword","sanqing" :),
     (: perform_action, "sword","jianzhang" :),
     (: perform_action, "sword","jianmang" :),
    }) );

setup();

        carry_object("/d/obj/cloth/baguapao")->wear();
//        carry_object("/d/sky/obj/yunxue")->wear();
        carry_object("/d/obj/weapon/sword/qinghong")->wield();
}
void init ()
{
  add_action("do_back", "back");
}
int accept_object(object who, object ob)
{
 if((string)ob->query("id") !="baiyu-ling"){
 command("say ��û����۵�����,��ô�ܸ��������«.");
 return 0;
}
else {  
 command("smile");
 command("say �����������«��ͬС��,����·�ϱ�������ȥ,����������۽���.");
 command("say ������ʤ����,����ܷ��ĵð���������!");
 this_player()->set_temp("laojun_fight", 1);
 return 1;
}
}
int accept_fight(object who)
{
 object me;
 me = this_object();
     if (!who->query_temp("laojun_fight")){
     command("say �޵�֮�˲�����������!!\n");
         return 0;
   }

 say("̫���Ͼ�Ц��:�����ϵ���ƴ�������Ϲ�ͷ,��������а�!\n");
  me->set("eff_kee", (int)me->query("max_kee"));
        me->set("kee", (int)me->query("max_kee"));
        me->set("eff_sen", (int)me->query("max_sen"));
        me->set("sen", (int)me->query("max_sen"));
     who->set_temp("laojun_fight",0);
     remove_call_out("check_fight");
     call_out("check_fight", 1, me, who);
     return 1;
}
void player_win(object me, object who)
{
       object hulu;

      hulu=new("/d/33tian/obj/hulu");
      command("sigh");
      say("̫���Ͼ�̾��:С���ɹ�Ȼ�Ƿ�����ǿ,���������������!!\n");
      hulu->move(who);
message_vision("̫���Ͼ���:�������«���վͽ���$N��,·�Ͽɵ�С����.\n",who);
}
void player_lose (object me, object who)
{
     string msg;
     msg = RANK_D->query_respect(who);

   command("jump");
   say("̫���Ͼ�Ц��:"+msg+"������Ҫ��������,�����ʸ����������«!\n");
}
void check_fight (object me, object who)
{
     int my_kee, whos_kee;
     int my_max_kee, whos_max_kee;

   if(!who) return;
     my_kee = me->query("kee");
     whos_kee = who->query("kee");
     my_max_kee = me->query("max_kee");
     whos_max_kee = who->query("max_kee");

     if (me->is_fighting()){
         call_out ("check_fight",1,me,who);
         return;
     }

     if (!present(who, environment(me)))
         return;
   if ((my_kee*100/my_max_kee) <= 50)
     player_win (me, who);
   else if ((whos_kee*100/whos_max_kee) <= 50)
     player_lose (me, who);
}

void die()
{

        if( environment() ) {
message("sound", "\n\n̫���Ͼ�ŭ��,������������������\n\n", environment());
message("sound", "\n˵������������ţ,���Ƴ����ض�ȥ������\n\n", environment());

        }

        destruct(this_object());
}
int do_back(string arg)
{
  object who = this_player();
  object me = this_object();
  string here = (string)environment(me);
  string there = who->query_temp("lingshan/from");

  message_vision("$N����$n��$N�ط���\n",who,me);
  //if (!there)
  //  there = "/d/city/kezhan";
  there = "/d/city/kezhan";

  who->set_temp("accept",0);
  message_vision("$Ņ�ֶ�$nһ�ġ���\n",me,who);
  who->move(there);
  message_vision("����һ����������ֻ��$N��������������\n",who);
  
  return 1;
}
void attempt_apprentice(object ob)
{
if ( (string)ob->query("family/family_name")=="��ׯ��") {
if (ob->query("obstacle/number") < 26) {
command("say ��λ" + RANK_D->query_respect(ob) + "�㻹���ȳ�ȥ����һ���ɣ�\n");
command("shrug");
return;
        }
  if (((int)ob->query("daoxing") < 1000000 )) {
   command("say " + RANK_D->query_respect(ob) +
"�ĵ��в��������Щ��ѧ�ط�������������\n");
   return;
   }
        command("pat "+ob->query("id"));
        command("say �ã��Ҿ��������ˡ�\n");
command("recruit " + ob->query("id") );
        return;
   }
   command("shake");
   command("say " + RANK_D->query_respect(ob) +
"ˡ������׾,��λ��.....\n");
        return;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob) )
    ob->set("class", "xian");
    ob->set("title", HIW"���ʹ������洫"NOR);
}
string ask_wuxing()
{
	object me = this_player();
	object downroom = load_object(__DIR__"wuxing");
	if( !wizardp(me) && me->query("family/family_name") != "��ׯ��" )	
		return ("��������ׯ�۵��ӣ���ζ�������̫��֮��");
	if( me->query("betray/count") )
		return ("�����Ķ����޷�������о�ѧ��\n");
	if( me->query("wuxing_known") > 2 )
		return ("�����еĵ����㶼���ˣ������Ҫ�����Լ����ˣ�");
	if( me->query("wuxing_cant") )
		return ("��ѧ���㶼ѧ���ˣ�����ѧ�ģ���Ҳ��᲻�ˣ�ĪҪǿ��");
	if( !me->query("wuxing_known"))
	{
		if( me->query_skill("literate",1) < 200 )
			return ("�������ѧʶ������ܶ�������̫����");
		if( me->query_skill("wuxing-quan",1) < 200 )
			return ("������ȭ�Ļ���̫���ο��˰ɣ�");
		if( me->query_skill("zhenyuan-force",1) < 200 )
			return ("�������Ƕ�һ���ˣ�����������Ԫ�񹦵Ļ�������ʱ��������δ������������֮�ǰ���");
	}
	if(me->query("wuxing_known")==1)
	{
		if( me->query_skill("literate",1) < 250 )
			return ("Ҫѧ���������̫���������ѧʶ��������");
		if( me->query_skill("wuxing-quan",1) < 250 )
			return ("Ҫѧ���������̫���������ȭ����������");
		if( me->query_skill("zhenyuan-force",1) < 250 )
			return ("Ҫѧ���������̫����������ڹ���������");	
	}
	if(me->query("wuxing_known")==2)
	{
		if( me->query_skill("literate",1) < 300 )
			return ("Ҫѧ���������̫���������ѧʶ��������");
		if( me->query_skill("wuxing-quan",1) < 300 )
			return ("Ҫѧ���������̫���������ȭ����������");
		if( me->query_skill("zhenyuan-force",1) < 300 )
			return ("Ҫѧ���������̫����������ڹ���������");	
	}
	me->set_temp("wuxing_learn",1);
	command("say �ã��Ҿ�����һ�̣���������������о�ѧ��");
	message_vision(HIC "̫���Ͼ�����һ�ӣ���ֻ�����ܾ���ɿ�仯��һ�ᵽ��һ����ȫİ���ĵط���\n" NOR, me);
	me->move("/d/33tian/wuxing");
	message_vision(HIC "ֻ��ſ����һ�����Ӱ���е���һ��������\n" NOR, downroom);
	return ("����ׯ�۹�Ȼ�˲żüã�");
}