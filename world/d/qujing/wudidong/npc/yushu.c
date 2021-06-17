
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// yushu.c, ����
// created by mes, updated 6-20-97 pickle
// updated again by pickle on 9-2-97, to open her menpai

/************************************************************/

// declarations and variables

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
   string ask_mieyao();
   string ask_cancel();
string say_key();
string ask_daojian();
void punish_player(object me);
   string ask_swear();
int accept_object(object me, object ob);

/************************************************************/
void create()
{
  set_name("����", ({"yu shu","yushu", "shu", "monster"}));
    set_weight(1000000);
  set("gender", "Ů��" );
  set("age", 23);
  set("long", 
"���������޵׶��Ķ����ˡ������޵�����������������������\n"
"Ҳ��֪Ϊʲô��ʻ�δ���ɱ���Χ�ˡ���˵�����칬���ף�Ҳ\n"
"��֪��١�\n");
  set("title", "��ӿ����");
  set("combat_exp", 1500000);
  set("attitude", "heroic");
  set("daoxing", 3000000);
  create_family("�ݿ�ɽ�޵׶�", 1, "����");
  set("int", 25+random(5));
  set("cor", 30+random(10));
  set_skill("unarmed", 150);
  set_skill("dodge", 180);
  set_skill("parry", 160);
  set_skill("spells", 160); 
  set_skill("yaofa", 160);
  set_skill("sword",190);
  set_skill("qixiu-jian",190);
  set_skill("blade", 180);
  set_skill("kugu-blade", 200);
  set_skill("lingfu-steps", 150);
  set_skill("yinfeng-zhua", 150);
  set_skill("force", 180);   
  set_skill("huntian-qigong", 180);
  map_skill("force", "huntian-qigong");
  map_skill("spells", "yaofa");
  map_skill("unarmed", "yinfeng-zhua");
  map_skill("sword", "qixiu-jian");
  map_skill("parry", "kugu-blade");
  map_skill("blade", "kugu-blade");
  map_skill("dodge", "lingfu-steps");
  set("per", 50);
  set("max_kee", 2500);
  set("max_sen", 2500);
  set("force", 3800);
  set("max_force", 2000);
  set("force_factor", 150);
  set("mana",3000);
  set("max_mana", 3000);
  set("mana_factor", 50);
  set("inquiry",([
 "����" : (: ask_mieyao :),
    "cancel" : (: ask_cancel :),
       "key": (: say_key :),
       "Կ��": (: say_key :),
       "name": "����������޵׶��Ŀ�ɽ��ʦ��",
    //"����" : (: ask_swear :),
    "����" : (: ask_daojian :),
       "here": "��������ݿ�ɽ�޵׶����������ʮ�������Ҳ�κ��Ҳ��ã�",
       "rumors": "����ո�ץסһ�����С��������Ͼ�������������ˡ�",
       "�������": "���ʣ����˲���ȥ�ҳ��ӣ�",
       "����": "�ٺ٣��������������ء��������Ӹɾ��˾Ϳ��������˳��ˡ�\n"
          "����Ҳ������ȥ�������ˡ�˵�������Ѿ������ˡ�",
       "����": "Ҫ����Ҳ�У����ǲ�֪���Ұ�Կ�׷��Ķ��ˡ�",
       ]));
  set("chat_chance_combat", 60);
   
   set("chat_msg_combat", ({
     (: exert_function, "zhangqi" :),
        (: perform_action,"blade", "pozhan" :),
        (: perform_action,"blade", "diyu" :),
   }) );
  setup();
  carry_object("/d/obj/weapon/blade/yanblade")->wield();
  carry_object("/d/obj/cloth/nichang")->wear();
  carry_object("/d/obj/cloth/yuanxiang")->wear();
}
/**************************************************************/
string ask_cancel()
{
    object me=this_player();
if((int)me->query_temp("m_mieyao"))
{
      me->add("daoxing",-2000);
      me->delete_temp("m_mieyao");
      me->delete("secmieyao");
      me->delete("secmieyao/type");
      me->delete("secmieyao/location");
      me->delete("secmieyao/place");
      me->delete("secmieyao/name");
      me->delete("secmieyao/id");
     return ("û�õĶ�����");
}
else
{
     return ("���������𣿣�");
}
}
string ask_mieyao()
{
   object me=this_player();

    if(me->query("family/family_name")!="�ݿ�ɽ�޵׶�")
      return ("�㲻�Ǳ�������!");

   command("pat "+me->query("id"));
    command("say ��־����");
   return "/d/obj/mieyao"->query_yao(me);
}

int attempt_apprentice(object me)
{
  string myname=RANK_D->query_rude(me);
  string myid=me->query("id");
  command("look "+myid);
  command("consider");
  if(me->query("family/master_id") != "tian shu" && me->query("combat_exp") < 200000)
  {
      command("say ʲô���������ҹ���");
      return 1;
  }
  if (me->query("wudidong/sell_reward") < me->query("combat_exp") / 20)
  {
    command("say "+myname+"Ҫ���������£��ȶ�ȥŪЩ�����������￴���ĳϣ����ʦ�ͺ������ˡ�");
    return 1;
  }
  if (me->query_skill("huntian-qigong", 1) < 50 && me->query("combat_exp") < 200000)
  {
    command("say "+me->name()+"��������ƾ�ǵ㱾�»����䣡");
    return 1;
  }
  command("grin");
  command("say ���������������ˡ�"+myname+"�����˶������Ū��ԭ�ϣ�");
  command("recruit "+myid);
  return 1;
}
int recruit_apprentice(object ob)
{
  if( ::recruit_apprentice(ob))
  {
    ob->set("class", "yaomo");
  ob->set("title", YEL"�ݿ�ɽ��ӿ�������µ���"NOR);
  }
}
/************************************************************/

// the prevent learn series... first yushu tosses the player
// if he's saved the monk, and second she has condition of
// learning kugu-blade.

int prevent_learn(object me, string skill)
{
  int mykugu=me->query_skill("kugu-blade", 1);
  if (wizardp(me) && me->query("env/immortal"))
    return 0;
  if (skill == "kugu-blade")
  {
      if (mykugu>=200)
      {
   command("say �����ò��������̣��ѵ�������ǲ����ģ�");
   return 1;
      }
      if (mykugu<200 && me->query("wudidong/given_book_3")) return 0;
      if (mykugu<141 && me->query("wudidong/given_book_2")) return 0;
      if (mykugu<=81 && me->query("wudidong/given_book_1")) return 0;
      command("say ���̣������޵׶�����֮�ܣ�");
      return 1;

    }
  if (skill == "yaofa" && me->query("obstacle/wudidong")=="done")
  {
      call_out("punish_player", 1, me);
      return 1;
  }
  return 0;
}
int accept_object(object me, object ob)
{
    int volume;
    if(ob->query("name_recognized") != "�ݹǵ�����")
        return notify_fail(CYN"����ŭ�������ʣ����ֲ��������õģ�\n"NOR);
    volume=ob->query("��");
    me->set("wudidong/given_book_"+(string)volume, 1);
    if (me->query("family/master_id") != "yu shu")
   command("say �ţ���Ȼ���������Ե�����ŵ�ԣ�����Ϊͽ��");
    command("recruit "+me->query("id"));
    if (me->query("family/master_id") == "yu shu")
   command("say ��ͽ�ܣ���Ȼ������ʦ����һ�����̡�");
    return 1;
}

void punish_player(object me)
{
    object *inv, ob;
    int i;
    inv=all_inventory(me);
    i=(int)sizeof(inv);
    while(i--)
    {
        ob=present(inv[i],me);
        destruct(ob);
        continue;
    }
    command("say "+me->name()+"������ʣ�����ȥ�úÿ�������ͺ¿���㾹�Ұ����������ˣ�");
    command("say ��ô�ĵ��ӣ����һ���������ѧ���£�");
    command("say ���úý�ѵ��ѵ�㣬���˻�����Ϊ�����Ǻ��۸����ˣ�");
    message_vision("ֻ�������������˸��������������дʣ���$N�ȵ�������\n", me);
    me->unconcious();
    message_vision("��������С��������$N������һ�ӡ�$N�����ˣ�\n", me);
    me->move("/d/qujing/wudidong/punish");
    message("vision", "ֻ�����ˡ���һ����$N����������\n", me);
    return;
}
/*********************************************************************/
string say_key()
{
  object me=this_player(), ob, npc=this_object();
  int mykar=me->query_kar();
  int real_key_condition;

  if(npc->is_fighting() || me->is_fighting())
    return ("û�ţ����ŵ㣡");
  if (member_array("tian shu",me->parse_command_id_list())==-1 )
    {
      call_out("killplayer", 1, me);
      return ("�Ķ�����"+RANK_D->query_rude(me)+"��������");
    }
  message_vision(CYN"�����$N˵�����ðɣ���ȥ����\n"NOR, me);
  if (npc->query_temp("gave_out_key"))
      real_key_condition=0;
  else real_key_condition=1;
  if (!real_key_condition)
    {
      ob=new("/d/qujing/wudidong/obj/key-fake");
    }
  else if (random(mykar)>8)
    {
      ob=new("/d/qujing/wudidong/obj/key-real");
      npc->set_temp("gave_out_key", 1);
    }
  else ob=new("/d/qujing/wudidong/obj/key-fake");
  ob->move(me);
  me->set_temp("mark/wudidong_yushu_gave_me_key", 1);
  return ("�úÿ�����ͺ¿��\n");
}
void killplayer(object me)
{
  this_object()->kill_ob(me);
}
/**************************************************************/
void init()
{
//       add_action("do_swear", "swear");
  object me;

  ::init();
  if( interactive(me = this_player()) && !is_fighting() ) {
    call_out("greeting", 1, me);
  }
}
void greeting(object me)
{
  int myspells=me->query_skill("spells");
  int mykar=me->query_kar();
  string npcname=this_object()->query("name");
  string npcrude=RANK_D->query_self_rude(this_object());
  string myrude=RANK_D->query_rude(me);

  if( !me || environment(me) != environment() ) return;
  if( me->query("family/family_name") == "�ݿ�ɽ�޵׶�")
    return;
  if( member_array("yu shu", me->parse_command_id_list())!=-1)
    {
      command("say �ĸ����ˣ����ұ��"+npcrude+"������ҡײƭ����������");
      kill_ob(me);
      return;
    }
  if( member_array("tian shu",me->parse_command_id_list())==-1 )
    {
      command("say ��������"+myrude+"���޵׶���������Ұ�ĵط�����������");
      command("kill " + me->query("id"));
      return;
    }
  if( random(mykar) > 8) return;
  else
    {
      message_vision(CYN ""+npcname+"��$N��ȵ���߾��ʲô�������������"+RANK_D->query_self_rude(this_object())+"�������ȥ��\n"NOR, me);
      message_vision(npcname+"��һ�����֣�$N��ʱ�ֳ�ԭ�Σ�ԭ����"+me->query("name")+"��\n", me);
      me->delete_temp("spellslevel");
      me->delete_temp("d_mana");
      me->delete_temp("apply/name");
      me->delete_temp("apply/id");
      me->delete_temp("apply/short");
      me->delete_temp("apply/long"); 
      kill_ob(me);
      return;
    }
}



//int do_swear()
string ask_swear()
{
	object me;
	int amount,i;
	mapping skills;
	string *skillsname;
	me=this_player();
        me->command("say ��Ը��Ч�ҷ��ˣ���Զ���޵׶��ĺõ��ӡ�");
	if (mapp(skills = me->query_skills()))
            {
               skills = me->query_skills();
               skillsname = keys(skills);
               amount = sizeof(skills);
               for (i = 0; i < amount; i++)
                {if (skillsname[i]!="qixiu-jian"
                     && skillsname[i]!="kugu-blade"
                     && skillsname[i]!="yinfeng-zhua"
                     && skillsname[i]!="daya-jian"
                     && skillsname[i]!="yaofa"
                     && skillsname[i]!="huntian-qigong"
                     && skillsname[i]!="blade"
                     && skillsname[i]!="dodge"
                    && skillsname[i]!="lingfu-steps"
                     && skillsname[i]!="stealing"
                     && skillsname[i]!="sword"
                     && skillsname[i]!="parry"
                     && skillsname[i]!="unarmed"
                     && skillsname[i]!="literate"
                     && skillsname[i]!="force"
                     && skillsname[i]!="spells")
                    {command("say �����������ɵ��书������������㣿"); 
//return 1;}  
return ("�㲻�Ǳ�������!");
}
                  }
                     command("say �ã�ϣ�����ܵ��������޵׶������Σ�Ϊ�������⡣");
                     me->delete("betray/count", 1);
                     me->delete("betray/wudidong", 1);
                     me->delete("betrayer", 1);
                     me->set("maximum_force",me->query("max_force"));
            }        
return ("�ú�Ŭ��!");
}    

string ask_daojian()
{
	object me = this_player();
	object ts,swk,zbj,shs,lijing,nezha;
	if( !wizardp(me) && me->query("family/family_name") != "�ݿ�ɽ�޵׶�" )	
		return ("�㲻�����ݿ�ɽ�޵׶����ӣ�");
	if( me->query("betray/count") )
		return ("�����Ķ����޷���ᵶ����ѧ��\n");
	if( me->query("daojian_known") > 2 )
		return ("������ѧ���㶼�Ѿ�ѧ���˰���");
	if( me->query("daojian_cant") )
		return ("��ѧ���㶼ѧ���ˣ�����ѧ�ģ���Ҳ��᲻�ˣ�ĪҪǿ��");
	if( me->query_skill("literate",1) < 200 )
		return ("�������ѧʶ�������ѧ�ᵶ����ѧ��");
	if( me->query_skill("yinfeng-zhua",1) < 200 )
		return ("�������ȭ�Ź��������ѧ�ᵶ����ѧ��");
	if( me->query_skill("kugu-blade",1) < 200 )
		return ("������㵶���������ѧ�ᵶ����ѧ��");
	if( me->query_skill("qixiu-jian",1) < 200 )
		return ("������㽣���������ѧ�ᵶ����ѧ��");
	if( me->query_skill("huntian-qigong",1) < 200 )
		return ("��������ڹ��������ѧ�ᵶ����ѧ��");
	if( !me->query("daojian_known") )
	{
		if( !me->query_temp("daojian/zbj") )
		{
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��ɮ"+NOR"��ͽ���ǣ���һ���޼ʵ�ƽҰ��������һ�����̣���֪����û������ѽ��\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"��ʦ�����⻹���򵥣��ð˽�ȥ��̽һ��������֪�������𣿺ٺ�...\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�˽�"+NOR"���ߣ����������ֵ���ͷ������...\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"�����ӣ�����͵����Ҫ����ɳʦ��ȥ��̽�����������\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"ɳɮ"+NOR"��������ʦ���⵽���أ�ʦ��������������Ϣ����ȥȥ������\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��ɮ"+NOR"���򾻣����������ۣ�������Ϣһ�°ɣ����ܣ����ȥ��̽һ������ȥ��أ�ĪҪ�����г̡�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�˽�"+NOR"������...��ʦ����������ȥ��...\n"NOR,users());
			me->set_temp("daojian/zbj","begin");
			zbj = new("/d/qujing/wudidong/npc/zbj.c");
			zbj->set("owner",me);
			zbj->move("/d/qujing/wudidong/firemount-wudidong2");
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�˽�"+NOR"��ǰ��պ��и�Сɽͷ����ȥ������\n"NOR,users());
			return ("��˵��ɮʦͽ�������żҴ壬��˽�����̽·����ȥ���Ұ���ץ����������");
		}
		else if( me->query_temp("daojian/zbj") == "begin" )
		{
			return ("������ȥץ��˽䣿��");
		}
		else if( me->query_temp("daojian/zbj") == "done" && !me->query_temp("daojian/ts") )
		{
			me->set_temp("daojian/ts","begin");
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��ɮ"+NOR"����գ��˽�ȥ����ô�ã���ô��û�������������������˰ɣ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"��ʦ�����ҿ��⸽���������أ��˽䶨�ܶԸ����ˣ����ͱ��ż��ˡ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��ɮ"+NOR"����գ�����ô�������Դ�ʦ�ܣ���ȥ���������������֣�����Ҳ������·��\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"��"+me->name()+"�����úã�����ȥ������������գ������Գ�������ɮץ�ض�������\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+me->name()+NOR"���ǣ����ˣ�"+me->name()+"ʹ�˸����ݣ�������Сɽͷ�ϣ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"�����ã����ص�������ɳʦ�ܣ��㿴��ʦ������ȥȥ������\n"NOR,users());
			swk = new("/d/qujing/wudidong/npc/swk.c");
			swk->set("owner",me);
			swk->move("/d/qujing/wudidong/firemount-wudidong2");
			me->move("/d/qujing/wudidong/firemount-wudidong2");
			return ("�����ˣ�");
		}
		else if( me->query_temp("daojian/zbj") == "done" && me->query_temp("daojian/ts") == "begin" )
		{
			return ("������ȥ��������գ����ҵ����Ժ�����Գû����ߣ�");
		}
		else if( me->query_temp("daojian/zbj") == "done" && me->query_temp("daojian/ts") == "done" )
		{
			me->start_busy(5);
			if( random( me->query("int")) > 10 )
				call_out("finish1",2,me);
			else
				call_out("finish2",2,me);
			return ("����ץ����ɮ���㹦����û������ʹ��㵶����һ�εĿھ����ܲ������򣬾Ϳ���������ˣ�");
		}
		else
		{
			return ("û�õĶ�����������˼�������ң���");
		}
	}
	if( me->query("daojian_known") == 1 )
	{
		if( !me->query_temp("daojian/swk") )
		{
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"��ʦ����ʦ����ʦ��...\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"���ɶ���������ƻ�����������������ҳ���...\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"����ʥ����ʥ����С��������ʲô���飿\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"�����أ���ؽ��ϳ���������������ʦ����ץ���ˣ����֪�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"��������ʥ����������֪��������������ǿ��С��ʵ�ڲ��Ƕ��ְ���\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"���ߣ�������һ�ף������֪�������Ķ������ڣ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"������²���һ����ɽ��ɽ����һ�����Ϊ����ף����Ի������޵׶���������ǰ��������ռ��ȥ��\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"�������ȥ�������������ʦ����\n"NOR,users());
			me->set_temp("daojian/swk","begin");
			swk = new("/d/qujing/wudidong/npc/swk.c");
			swk->set("owner",me);
			swk->move("/d/qujing/wudidong/dong1");
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"���ţ�Ӧ�þ��������ˣ������һ�������붴�У����²�������������������ǧ�㡣\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"���ߣ��ⶴ���ˡ�����¡¡��������վ���𹿰����������Ҹ����顣\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"���������Ͻ�����ʦ���ͳ�������Ȼ����ÿ�������\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"����ѽ�������ˣ�����մ��������ˣ�"+me->name()+"����Ͻ�����ȥ�������ߣ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+me->name()+NOR"���ǣ����ˣ�"+me->name()+"ʹ�˸����ݣ������˶��ţ�\n"NOR,users());
			me->move("/d/qujing/wudidong/dong1");
			return ("�����ˣ�");
		}
		else if( me->query_temp("daojian/swk") == "begin" )
		{
			return ("������ȥ������ո��ߣ���");
		}
		else if( me->query_temp("daojian/swk") == "done" )
		{
			me->start_busy(5);
			if( random( me->query("int")) > 16 )
				call_out("finish1",2,me);
			else
				call_out("finish2",2,me);
			return ("��������գ�����֤�����ܹ�ѧϰ����ĵ�����ѧ�ˣ�����ʹ��㵶���ڶ��εĿھ����ܲ������򣬾Ϳ���������ˣ�");
		}
		else
		{
			return ("û�õĶ�����������˼�������ң���");
		}
	}
	if( me->query("daojian_known") == 2 )
	{
		if( !me->query_temp("daojian/lijing") )
		{
			me->set_temp("daojian/lijing","begin");
			swk = new("/d/qujing/wudidong/npc/swk.c");
			swk->set("owner",me);
			swk->move("/d/qujing/wudidong/dong");
			lijing = new("/d/qujing/wudidong/npc/lijing.c");
			lijing->set("owner",me);
			lijing->move("/d/qujing/wudidong/dong");
			nezha = new("/d/qujing/wudidong/npc/nezha.c");
			nezha->set("owner",me);
			nezha->move("/d/qujing/wudidong/dong");
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"����������������...\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"����ʥ����ʥ��С����˵����������������������ף�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"�������硱��������\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��߸"+NOR"������������ô�ˣ���\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"������Ҫ��ʲô���·�����\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"�����棿��\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"����ʥ��С��Ҳֻ����˵����������������ǧ�������С�������ѽ������\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"�����£��ѵ������ﻹ������֮�ˣ��������һ�������������¥̨��\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"�������������������ң���Ȼ������ȥ����ۡ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��߸"+NOR"����ʥ������ô�п�������¥��������߸����˼�����������Ҫ�����ˣ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"����ʥ�����Һ��£���\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"����������������½�Ϊ����׽����ʦ�������֪�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"���ߣ������ݵ���ҥ��С���Ҵ�����콵�������£�������̰�֮�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��߸"+NOR"��˼���С�����\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"���һ�������ȥ������أ��б��������ץ�����������������...\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"����...��������...\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"��߸"+NOR"���������������������ݿ�ɽ������������һ����Ů��\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"��˼���С�����\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"���ߣ����Ҽ����ȥ��\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"����ѽ����ʥ���㿴...��ʵ�ڶԲ�����������̫�ã��Ҹ������ˣ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"���"+NOR"������ʶ�࣡\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"�"+NOR"����߸��̫�ӣ���ȥ׼����������ͬ��ʥ�½罵�������˼��������������ݿ�ɽ��\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+"����"+NOR"�������ˣ����常������������ˣ�"+me->name()+"�����޷����棬��ȥ���ҽ����Ǹ��ߣ�\n"NOR,users());
			message("system",HIW"��"+HIR+"����ȡ��"+HIW+"��"+HIY+me->name()+NOR"���ǣ����ˣ�"+me->name()+"ʹ�˸����ݣ�������ɽ����\n"NOR,users());
			me->move("/d/qujing/wudidong/dong");
			return ("�����ˣ�");
		}
		else if( me->query_temp("daojian/lijing") == "begin" )
		{
			return ("������ȥ����������Ǹ��ߣ���");
		}
		else if( me->query_temp("daojian/lijing") == "done" )
		{
			me->start_busy(5);
			if( random( me->query("int")) > 25 )
				call_out("finish1",2,me);
			else
				call_out("finish2",2,me);
			return ("��������ˣ�����֤�����ܹ�ѧϰ����ĵ�����ѧ�ˣ�����ʹ��㵶�������εĿھ����ܲ������򣬾Ϳ���������ˣ�");
		}
		else
		{
			return ("û�õĶ�����������˼�������ң���");
		}
	}
	return ("�ٺ٣�����");
}

void finish1( object me )
{
	message_vision(HIB"������$N���ߣ����������һ����µĿھ���\n" NOR,me);
	message_vision(HIB"$N��¶ϲɫ�����˵�ץ��������\n" NOR,me);
	me->delete_temp("daojian");
	me->add("daojian_known",1);
	if( me->query("daojian_known") == 1 )
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(yu shu)��" + me->name() + "����ץס��ɮ��ѧ����"+HIB"[����]"+HIC"��ѧ��\n\n\n"NOR,users());
	if( me->query("daojian_known") == 2 )
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(yu shu)��" + me->name() + "���һ�������գ���"+HIB"[����]"+HIC"��ѧ���������һ����\n\n\n"NOR,users());
	if( me->query("daojian_known") == 3 )
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(yu shu)��" + me->name() + "���һ�������ˣ���"+HIB"[����]"+HIC"��ѧ�����˵Ƿ��켫��\n\n\n"NOR,users());
	return ;
}

void finish2( object me )
{
	message_vision(HIB"������$N���ߣ����������һ����µĿھ���\n" NOR,me);
	message_vision(HIB"$Nüͷ���壬�ƺ��޷���ᣡ\n" NOR,me);
	me->delete_temp("daojian");
	me->set("daojian_cant",1);
	if( me->query("daojian_known") == 1 )
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(yu shu)��" + me->name() + "���һ�������գ���ϧ�޷���������"+HIB"[����]"+HIC"��ѧ��\n\n\n"NOR,users());
	else if( me->query("daojian_known") == 2 )
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(yu shu)��" + me->name() + "���һ�������ˣ���ϧ��Ե�������޷����"+HIB"[����]"+HIC"��ѧ����߾��磡\n\n\n"NOR,users());
	else
		message("chat",HIC+"\n\n��"+HIW+"����ҥ��"+HIC+"������(yu shu)��" + me->name() + "����ץס��ɮ����ϧ��"+HIB"[����]"+HIC"��ѧ��Ե��\n\n\n"NOR,users());
	return ;
}