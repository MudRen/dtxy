// tomcat
// 

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int begin_go();
string ask_sword();
void create()
{
        set_name("��ü", ({ "bai mei", "bai", "mei" }));
        set("title",HIW"��ɽ��ʦ"NOR);
        set("long", "��λ��ͷ�׷������ˣ�һ˫���׵ĳ�ü�ʹ���\n");

        set("gender", "����");
        set("age", 120);
        set("attitude", "peaceful");
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("per", 40);
        set("class","swordsman");
        
        set("kee", 8000);
        set("max_kee", 8000);
        set("sen", 8000);
        set("max_sen", 8000);
        set("force", 12000);
        set("max_force", 6000);
        set("max_mana",6000);
        set("mana",12000);
        set("force_factor", 400);
        set("mana_factor", 400);
        set("combat_exp", 10000000);
        set("daoxing", 10000000);

        set_skill("spells",300);
        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("sword", 300);
        set_skill("zixia-shengong", 300);
        set_skill("sevensteps", 300);
        set_skill("hunyuan-zhang", 300);
        set_skill("literate", 300);
        set_skill("unarmed", 300);
        set_skill("mindsword", 300);
        set_skill("yujianshu", 300);
        set_skill("taoism",300);
        map_skill("spells", "taoism");
        map_skill("dodge", "sevensteps");
        map_skill("force", "zixia-shengong");
        map_skill("parry", "mindsword");
        map_skill("sword", "yujianshu");
        map_skill("unarmed", "hunyuan-zhang");


 create_family("��ɽ��", 1, "��ʦ");
	set("sword_known",8);
        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: perform_action, "unarmed","fenguang" :),
                (: perform_action, "sword","wanjian" :),
                (: perform_action, "sword","sword" :),
                (: perform_action, "sword","duanshui" :),
                (: perform_action, "sword","fumo" :),
                (: cast_spell, "chaoyuan" :),                
        }) );
       set("inquiry", ([
                "��̨����"    : (: begin_go :),
                "����"    : (: ask_sword :),
       ]) );
        setup();
        
        carry_object("/d/obj/cloth/jinpao")->wear();
        carry_object("/d/obj/weapon/sword/qingfeng")->wield();
}
void attempt_apprentice(object ob)
{        
        if (ob->query_skill("yujianshu",1) < 180) {
        command("say ����ɽ�ɣ���ע�������������У����ҿ�" + RANK_D->query_respect(ob) + "�ǲ��Ǹö����¿๦�أ�");
                return ;
        }
        
        if ((int)ob->query("daoxing") < 1000000 ) {
  	command("say �����̫���ˡ�\n");
	return;
	}

        if (ob->query("obstacle/number") < 26) {
	command("say ��λ" + RANK_D->query_respect(ob) + "����Ϊʦ��Ҫ��������ȡ�����ѣ�\n");
	command("sigh");
	return;
	}        
        command("say �ðɣ��Ҿ��������ˡ�");
        command("recruit " + ob->query("id"));
        ob->set("class", "swordsman");
        ob->set("title",HIC"�������"NOR);
}

int begin_go()
{
  object me,ob;
 int dx,dx1,wx,qn;
 me=this_player();
 ob=this_object();
 dx=(me->query("daoxing"))/20;
if (dx>=100000) dx=100000;
 dx1=dx/1000;
 wx=(me->query("combat_exp"))/20;
if (wx>=10000) wx=10000;
 qn=30000;
 if (!me->query("fangcun/panlong_visite"))
 return 0;
 if (me->query("guanli/shushan"))
  return 0;
          if (me->query("fangcun/panlong_shushan")=="done")
{
     message_vision("\n��ü������Ц������,��,���������һ�ˣ�\n"NOR,me);
      message_vision(HIY"\n���������ü�Ͳ����ˣ�\n"NOR,me);
        ob->move("/d/lingtai/inside1");
    me->move("/d/lingtai/inside1");
      return 1;
}
if ((me->query_temp("fangcun/panlong_shushan_jiansheng")=="done")&&(me->query_temp("fangcun/panlong_shushan_jiujianxian")=="done")&&(me->query_temp("fangcun/panlong_shushan_lixiaoyao")=="done"))
{
   me->add("fangcun/panlong_visite",1);
   me->set("fangcun/panlong_shushan","done");
     message("chat",HIC+"��"+HIW+"��������"+HIC+"����ü(Bai mei)��"+me->query("name")+"������ͽ��ͽ������,��ʱ��ɽ��һ��ǰ����̨����\n"NOR,users());
  message("chat",HIC+"��"+HIW+"��������"+HIC+"����ü(Bai mei)��"+me->query("name")+"�õ�����������"+chinese_number(dx1)+"�꣬��ѧ"+wx+"�㣬Ǳ��30000�㣮\n"NOR,users());
    if (me->query("family/family_name")=="����ɽ���Ƕ�")
            message_vision("\n��ü������ʱ����" + RANK_D->query_respect(me) + "����֪ͨ����һ��.\n"NOR,me);
   me->add("daoxing",dx);
   me->add("combat_exp",wx);
  me->add("potential",30000);
 if ((me->query("family/family_name")!="����ɽ���Ƕ�")||(me->query("fangcun/panlong_noway")))
    me->set("guanli/shushan",1);
 return 1;
}
 if (me->query_temp("fangcun/panlong_shushan_laozu")=="begin")
{
      message_vision("\n��ü���������������õ�����\n"NOR,me);
     return 1;
}
 if (me->query_temp("fangcun/panlong_shushan_jiansheng")=="begin")
{
message_vision("\n��ü�����۾��������´�����һ��$N,Ȼ�󻺻�˵��.\n\n"NOR,me);
        call_out("begin_go1",3);
        return 1;
}
 command("shake " + me->query("id"));
  return 1;
}

int begin_go1()
{
 object me;
 me=this_player();
 command("say ���Ǻ��Ӻ�,����ɽһֱû���ֹ��˲�,����������ǧ������Ҫ��
               ������,�����������ϵ�֮��������Ȼ���ϵ�ʿ�������룬�Ҿ�����
        һ�ˣ���������Ҫ�õ�������ͽ����������ңͽ������");
me->set_temp("fangcun/panlong_shushan_laozu","begin");
}

int accept_object(object me, object ob)
{
 string myname=RANK_D->query_respect(me), thing=(string)ob->query("id");
 if ((me->query_temp("fangcun/panlong_shushan_jiansheng") == "begin")||(me->query_temp("fangcun/panlong_shushan_jiansheng") == "done"))
{
   if ((string)ob->query("id") == "jiansheng xinwu")
{
 command ("nod");
 command ("say û��,���Ҵ�ͽ�ܵĶ�����");
 me->set_temp("fangcun/panlong_shushan_jiansheng","done");
 return 1;
}
if (ob->query("id") == "jiujianxian xinwu")
{
command ("haha");
 command ("say ����,���Ҷ�ͽ�����ϵ��ǹɾ�ζ��");
me->set_temp("fangcun/panlong_shushan_jiujianxian","done");
 return 1;
}
if (ob->query("id") == "lixiaoyao xinwu")
{
command ("sigh");
command ("say ��������Сͽ������Щʱ���ˣ�");
 me->set_temp("fangcun/panlong_shushan_lixiaoyao","done");
return 1;
}
 else
{
command ("say ����ʲô��");
 return 1;
}
}
 else
{
 command ("say �󵨿�ͽ,������ɽ���ң� ");
 message_vision("\n\n��ü����һ��,$N��ʱ��׹����������.Ҳ��֪�������������\n\n"NOR,me);
 me->move("/d/city/kezhan");
 return 0;
}
}
void destroy(object ob)
{
 destruct(ob);
return;
}
void dropthing(string thing)
{
 command("drop "+thing);
return;
}
string ask_sword()
{
	object me = this_player();
	object weapon,jianling,user;
	if( me->query("betray/count") )
		return ("�����Ķ����޷������ɽ��ѧ��\n");
	if(me->query("family/family_name") != "��ɽ��" )
                return ("�㲻������ɽ����!!\n");
        if(me->query("sword_cant"))
      		return ("���޷�������ߵĽ��ģ�");
        if(me->query("sword_known") > 7 )
      		return ("���ĵĿھ��㶼�Ѿ�֪���˰���");
      	if( me->query_skill("literate",1) < 200 )
		return ("�����ѧʶ�����������ģ�");
	if( me->query_skill("yujianshu",1) < 200 )
		return ("����㽣�������������ģ�");
	if( me->query_skill("zixia-shengong",1) < 200 )
		return ("������ڹ������������ģ�");	
    	if (!objectp(weapon = me->query_temp("weapon")) ||
		(string)(weapon->query("skill_type")) != "sword")
	{
		return ("��û�д�������ô�����ģ� :)\n");
	}
      	command("smile");
	command("say �ã���Ȼ�Ѿ���ᵽ�˽��ģ�����ɽ��������ˣ�");
	jianling = present("jian ling",load_object("/d/shushan/shengdi/sword_room"));
	if( jianling )
	{
		user = present(jianling->query("owner"),load_object("/d/shushan/shengdi/sword_room"));
		if( user )
			return ("ʥ���������˲����㻹�ǵȵȰɣ�");
		else
			destruct(jianling);
	}
	command("say ����ɽ��������Ӫ�����ٳ�һ��ʥ�أ�������и�����ҵ������ĵã����������һ�̣���úò���ĪҪ����ǰ����һƬ���ģ�");
	message_vision("\n\n��ü����һ��,$N��ʱ��׹����������.Ҳ��֪�������������\n\n"NOR,me);
 	me->move("/d/shushan/shengdi/kongdi");
	return ("����ɽ��Ȼ�˲żüã�");
}