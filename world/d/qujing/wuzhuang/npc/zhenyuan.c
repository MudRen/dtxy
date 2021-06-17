// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// zhenyuan.c...weiqi, 98.02.24.
// copied a lot of useful functions from "rulai.c"...thanks snowcat:)

#define DEBUG 0
#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string expell_me(object me);
string keyword(object me);
string sword_xiaofeng(object me);
string sword_sanqing(object me);
string asked_guo(object me);
string ask_mieyao(object me);
string ask_cancel();
int begin_go();
int give_fu(object ob);

void create()
{
   set_name("��Ԫ����", ({"zhenyuan daxian", "zhenyuan", "daxian"}));
   set("title", "��ׯ�۹���");
   set("gender", "����" );
   set("age", 65);
   set("per", 24);
   set("str", 30);
   set("long", "���α����磬���������С���һλ����֮�棡\n");
   set("class", "xian");
   set("combat_exp", 5600000);
   set("attitude", "peaceful");
   create_family("��ׯ��", 1, "��ʦ");
   set("rank_info/respect", "����");
   set_skill("unarmed", 180);
   set_skill("wuxing-quan", 200);
   set_skill("dodge", 180);
   set_skill("baguazhen", 160);
   set_skill("parry", 180);
   set_skill("sword", 180);
   set_skill("sanqing-jian", 190);
   set_skill("staff", 160);
   set_skill("fumo-zhang", 190);
   set_skill("hammer", 160);
   set_skill("kaishan-chui", 190);
   set_skill("blade", 160);
   set_skill("yange-blade", 190);
   set_skill("force", 180);   
   set_skill("zhenyuan-force", 180);
   set_skill("literate", 180);
   set_skill("spells", 200);
   set_skill("taiyi", 200);
   map_skill("spells", "taiyi");
   map_skill("force", "zhenyuan-force");
   map_skill("unarmed", "wuxing-quan");
   map_skill("sword", "sanqing-jian");
   map_skill("dodge", "baguazhen");
   map_skill("staff", "fumo-zhang");
   map_skill("blade", "yange-blade");
   map_skill("hammer", "kaishan-chui");

   set("max_kee", 4500);
   set("max_sen", 4500);
   set("force", 5000);
   set("max_force", 2500);
   set("mana", 7000);
   set("max_mana", 3500);   
   set("force_factor", 200);
   set("mana_factor", 200);

   set("spell_qiankun_on", 1); //to use cast qiankun, must set this.
   set("chat_chance_combat", 90);
   set("chat_msg_combat", 
   ({
     (: cast_spell, "zhenhuo" :),
     (: cast_spell, "qiankun" :),
   }) );

   set("inquiry", ([
     "leave": (: expell_me :),
     "��̨����": (: begin_go :),
     "�뿪": (: expell_me :),
     "����Ǭ��": (: keyword :),
     "�ؾ�": (: keyword :),
     "name": "�Ϸ���Ԫ��\n",
     "here": "��������ׯ�ۣ�����ס�Ŀɲ��ǵ�ʿ��\n",
     "���彣��": (: sword_sanqing :),
     "������½���": (: sword_xiaofeng :),
     "������½�": (: sword_xiaofeng :),
     "���彣": (: sword_sanqing :),
     "sanqing-jian": (: sword_sanqing :),
     "xiaofeng-sword": (: sword_xiaofeng :),
     "�˲ι�": (: asked_guo :),
    "����": (: ask_mieyao :),
"���Է�":(:give_fu:),
      "cancel": (: ask_cancel :),
   ]) );

   setup();
   carry_object("/d/obj/cloth/xianpao")->wear();
   carry_object("/d/obj/weapon/sword/ruler")->wield();
}

/*
string ask_cancel()
{
    object me=this_player();
if(me->query("secmieyao"))
{
      me->add("daoxing",-2000);
      me->set("m_mieyao",1);
      me->delete("secmieyao_mudage");
      me->delete("secmieyao");
      me->delete("secmieyao/type");
      me->delete("secmieyao/location");
      me->delete("secmieyao/place");
      me->delete("secmieyao/name");
      me->delete("secmieyao/id");
      me->delete_temp("m_mieyao"); 
    return ("û�õĶ�����");
}
else
{
     return ("��Ҫ�����ң�");
}
}

*/

string sword_xiaofeng(object me)  
{
   me=this_player();
/*
   int i;
   i=query("sword_xiaofeng_number");  
   if (i>5)
    {
     message_vision("��Ԫ���ɵ����������ˣ�\n", me);
     message_vision("��Ԫ���ɵ������˰ɣ�����㿴���������˵��ˡ���������\n", me);
     message_vision("��Ԫ���ɸ��ֶ��Կ���ȥ�ˡ�������\n", me);
     return ("�������㻹�ǻ�ȥ�ɣ�����������\n");
    }
*/
   if((string)me->query("family/family_name")=="��ׯ��") {
     message_vision("\n��Ԫ���ɵ�ͷ����һ�������������\n", me);
    if(me->query("faith")<1000)
     return ("�����������㻹�Ƕ������ȥ�ɣ�\n");
     message_vision("��Ԫ���ɵ�ͷ��ϸ������һ�������������\n\n", me);
     if( me->query("sword_xiaofeng") == 1 ) 
     return ("�ղŲ��������㿴����\n");
     message_vision("��Ԫ����˳������һ��ľ����������һ�£�\n", me);
     if( (int) me->query("combat_exp") < 100000 ) return ("�����ڵ���̫�ͣ�ֻ�����������һ��ģ����\n");
     if( (int) me->query("max_mana") < 2200 ) return ("�����ڷ���̫�ͣ��޷�����\n");
     if(!me->query_skill("xiaofeng-sword")) return ("��û�����ž����ôҲ�������֣�\n");
     if(me->query_skill("sword",1)<180) 
          return ("�����������û�ڻ��ͨ���޷����������⹦��\n");
     if( (int)me->query_skill("xiaofeng-sword",1)<180) 
          return ("��������½�����û�ڻ��ͨ���޷����������⹦��\n");
     message_vision("��Ԫ���ɵ����ã����ٿ�һ��...��\n", me);
    if( random( (int) me->query_skill("sword",1)) > 100
         && random( (int) me->query("combat_exp")) > 100000
          && random(me->query("int"))<15 )
        {
          me->set("sword_xiaofeng", 1);
          message_vision("$N�����Ц�ˣ���������˼����......\n", me);
          command("haha");
          message_vision("��Ԫ���ɵ�ͷ������Ȼ���ҵĵ��ӣ�\n", me);
          message_vision("��Ԫ�����������������ɽ������׹���ҵ�������\n", me);
          return ("�úã������ڿ���ȥ�ˣ�\n");;
        }
//          me->set("sword_xiaofeng_number", i+1);
          command("hmm");
          command("shrug");
          message_vision("��Ԫ����̾��������Ȼ���ҵĵ��ӣ�����.....��������....��\n", me);
          message_vision("��Ԫ�����ƺ�������ʲô����.....\n", me);
          return ("���������ڿ���ȥ�ˣ�\n");
   }
          command("hmm");
          command("heng");
   message_vision("��Ԫ���ɿ�������ɱ����!!\n", me);
   return ("���̽�����ؼ����ô�ĵ��ӣ�\n");
}

string sword_sanqing(object me)  
{
   me=this_player();
/*
   int i;
   i=query("sword_sanqing_number");  
   if (i>5)
    {
     message_vision("��Ԫ���ɵ����������ˣ�\n", me);
     message_vision("��Ԫ���ɵ������˰ɣ�����㿴���������˵��ˡ���������\n", me);
     message_vision("��Ԫ���ɸ��ֶ��Կ���ȥ�ˡ�������\n", me);
     return ("�������㻹�ǻ�ȥ�ɣ�����������\n");
    }
*/
   if((string)me->query("family/family_name")=="��ׯ��") {
     message_vision("��Ԫ���ɵ�ͷ����һ�������������\n", me);
    if(me->query("faith")<1000)
     return ("�����������㻹�Ƕ������ȥ�ɣ�\n");
     message_vision("��Ԫ�����뵽ϸ��������Ц����������������\n\n", me);
     if( me->query("sword_sanqing") == 1 ) 
     return ("�ղŲ��������㿴����\n");
     message_vision("��Ԫ����˳������һ��ľ����������һ�£�\n", me);
     if( (int) me->query("combat_exp") < 100000 ) return ("�����ڵ���̫�ͣ�ֻ�����������һ��ģ����\n");
     if( (int) me->query("max_mana") < 2200 ) return ("�����ڷ���̫�ͣ��޷�����\n");
     if(!me->query_skill("sanqing-jian")) return ("��û�����ž����ôҲ�������֣�\n");
     if( me->query_skill("sanqing-jian",1) < 180 ) return ("�����Ž�����û�ڻ��ͨ���޷����������⹦��\n");
     if( me->query_skill("sword",1) < 180 ) return ("�����������û�ڻ��ͨ���޷����������⹦��\n");
     message_vision("��Ԫ���ɵ����ã����ٿ�һ��...��\n", me);
    if( random( (int) me->query_skill("sword",1)) > 100
         && random( (int) me->query("combat_exp")) > 100000
          && random(me->query("int"))<15 )
        {
          me->set("sword_sanqing", 1);
          message_vision("$N�����Ц�ˣ���������˼����......\n", me);
          command("haha");
          message_vision("��Ԫ���ɵ�ͷ������Ȼ���ҵĵ��ӣ�\n", me);
          message_vision("��Ԫ�����������������ɽ������׹���ҵ�������\n", me);
          return ("�úã������ڿ���ȥ�ˣ�\n");;
        }
          command("hmm");
         message_vision("��Ԫ����̾��������Ȼ���ҵĵ��ӣ�����.....��������....��\n", me);
          command("shrug");
          message_vision("��Ԫ�����ƺ�������ʲô����.....\n", me);
          return ("���������ڿ���ȥ�ˣ�\n");
   }
          command("heng");
          command("hmm");
   message_vision("��Ԫ���ɿ�������ɱ����!!\n", me);
   return ("���̽�����ؼ����ô�ĵ��ӣ�\n");
}

string ask_mieyao(object me)
{
    me=this_player();
     if((string)me->query("family/family_name")=="��ׯ��") {
//  if(me->query("faith")<100)
//      return ("�㻹���ȶ������Ϊ�");
    tell_room(environment(me),"��Ԫ���������д�.....\n");
    return "/d/obj/mieyao"->query_yao(me);
}
     return ("ƶ����֪��");
}
void attempt_apprentice(object ob)
{
   if( (string)ob->query("class")=="dao" )
     command("say �ã��ã����ɱ�һ�ҡ�\n");
   
  //}

   if( (string)ob->query("family/family_name")=="��ׯ��" )
   {
     if( (int)ob->query("family/generation") > 3   )
     {
        command("say ��»������������ռ������ӣ����ȵ��Ǳ߿����ɡ�\n");
     }
     else 
     {
        if( (int)ob->query("combat_exp") >= 300000 && (int)ob->query_skill("taiyi", 1) >= 120 )
        {
          command("nod ");
          command("say �ã�" + RANK_D->query_respect(ob) + "�����Ǳ��ŵ��˲ţ�\n");
          command("recruit " + ob->query("id") );
        }
        else
        {
          command("say �����Ͻ��ǲ�����������Ҫѭ�򽥽���\n");
        }
     }
   }

   else
   {
     command("nod");
     command("say ��λ" + RANK_D->query_respect(ob) + "�����Ž�������֮����֮�֡�һ�������Ϊ�������ӿ����Ĳ�����\n");
   }

   return;
}

int recruit_apprentice(object ob)
{
   if( ::recruit_apprentice(ob) )
     ob->set("class", "xian");
}

string expell_me(object me)
{       
   me=this_player();
   if((string)me->query("family/family_name")=="��ׯ��") {
     message_vision("��Ԫ���ɵ������ȻҪ�ߣ���Ҳ����ǿ��������̫���ɷ�����ׯ�۲���֮�أ��ɲ��ܴ������⡣\n", me);
     me->set_temp("asked_leave_wzg", 1);
     return ("�������Ҫ��(true)��\n");
   }
   return ("��磬���£��Ϳͣ�\n");
}

string keyword(object me)
{       
   me=this_player();
   if((string)me->query("family/family_name")=="��ׯ��") {
     message_vision("��Ԫ���ɵ�������ָ����Ǭ������������ɡ�\n", me);
     if( me->query("spell_qiankun_on") == 1 ) return ("�����Ѿ�����������\n");
     if( (int) me->query("combat_exp") < 10000 ) return ("�����ڵ���̫�ͣ�ʩ������Ǭ����Σ��������\n");
     if( (int) me->query("max_mana") < 300 ) return ("�����ڷ���̫�ͣ�ʩ������Ǭ����Σ��������\n");
     message_vision("��Ԫ���ɵ����ã�������...�԰�������$Nͷ��һ�ģ�\n", me);
     me->set("spell_qiankun_on", 1);
     return ("��������Ѿ��������ˣ�ȥ�գ�\n");
   }
   command("kick");
   return ("���̽�����ؼ����ô�ĵ��ӣ�\n");
}


void init()
{
        
     object ob = this_player();
        if( ob->query_temp("kill_tree") )
        {
        command("say С��ë����������ҵ��˲ι����Ȼ����Ϸ򲻿����ˡ�");
        command("slap "+ob->query("id"));
        }
		if((ob->query_temp("get_guo")<=3 )&&(ob->query("fangcun/panlong_wzg_rsg")!="done")&&(ob->query("fangcun/panlong_wzg_baxian")=="done"))
	    {
     	     message_vision("��Ԫ���ɶ�$N�������ǽ��������������𣿣�\n\n",ob);
		}
		if( ob->query_temp("get_guo")>=4 )
        {
			call_out("finish_wzg",2,ob);
		}
   add_action("do_true", "true");
   add_action("do_back", "back");
}

void finish_wzg(object me)
{
	if((!present("jinji zi",me))||(!present("dan pan",me)))
       {
   	     message_vision("��Ԫ���ɶ�$N����" + RANK_D->query_respect(me) + "�ҵĽ���Ӻ͵����أ�\n\n",me);
         return;
        }	
	command("pat "+me->query("id"));
    message_vision("\n\n��Ԫ����Ц���еĶ�$N˵����" + RANK_D->query_respect(me) + "������ׯ����Щ����û��ʲô���д�������
	�ι�������ׯ�۱���һ�ž�����ʦ����������Ϸ�������̨����ĺ���
	һ�Ż�����" + RANK_D->query_respect(me) + "�͵���ɽ���Ҿ����������森һ�ŵ�Ȼ��С�ֵ��Լ�
	�ˣ�����" + RANK_D->query_respect(me) + "��Ҫ�мǣ������˲ι�����������֮ʱ�������"+HIW"���Ƹ�
	"+NOR"������һ·"+HIY"����"+NOR"ʮ���ǧ��ֱ��"+HIW"���۱���"+NOR"�����Գ�" + RANK_D->query_respect(me) + "֮���ģ�\n\n", me);
	if( me->query_temp("get_guo")>=5 )
         me->set("fangcun/panlong_nowaywzg1",1);
	 me->set("fangcun/panlong_nowaywzg2",1);
	 me->set("fangcun/panlong_nowaywzg3",1);
	 destruct(present("jinji zi",me));
     destruct(present("dan pan",me));
	  
	     me->set("fangcun/panlong_wzg_rsg","done");
		 me->delete_temp("get_guo");
	call_out("cut_jinpan",1,me);
}

void cut_jinpan(object me)
{
     message_vision(HIY"\n\n��Ԫ���ɹ�����Ц������һ�ӣ���ʱ��$N���ϵĽ���Ӻ͵������˻�ȥ��\n\n"NOR,me);
}

int do_true(string arg)
{
   if(this_player()->query_temp("asked_leave_wzg")) {
     message_vision("$N���������������ߣ�\n\n", this_player());
     message_vision("��Ԫ����̾�˿��������ã��������ǿ͡�\n", this_player());
     this_player()->add("betray/wuzhuangguan", 1);
     this_player()->add("betray/count", 1);
     this_player()->set("combat_exp", this_player()->query("combat_exp")/100*80);
     this_player()->set("daoxing", this_player()->query("daoxing")/100*80);
     this_player()->delete_skill("taiyi");
     this_player()->delete("family");
     this_player()->set("faith",0);
     this_player()->delete("class");
     this_player()->set("title", "��ͨ����");
     this_player()->delete_temp("asked_leave_wzg");
     this_player()->delete("spell_qiankun_on");
     this_player()->save();
     message_vision("˵����$Nͷ��һ����$Nֻ������һ�ᣬ�յ����غ�����ʲô��\n", this_player());
     return 1;
   }
   return 0;
}

//the following is for renshen dahui...

void announce (object me, string str)
{
   if (DEBUG)
   { 
     object weiqi = find_player ("weiqi");
     if (weiqi && wizardp(weiqi))
        tell_object (weiqi,"�� "+str+"\n");
   }
   else
   {
     CHANNEL_D->do_channel(me,"chat",str);
   }
}

void start_renshen()
{
   object me;

   me = this_object();
    
   set_temp("invite","public");

   announce (me, "��ׯ���˲ι�Ʒ����ἴ����ʼ��\n");
   set_temp("give_num",0);
   call_out("ready1", 10);
   set_temp("ready0", 1);
}

void ready1()
{
   object me;

   me = this_object();

   announce (me, "��ׯ���˲ι�Ʒ��������Ͼ�Ҫ��ʼ��\n");
   call_out("ready2", 5);
   set_temp("ready1", 1);
}

void ready2()
{
   object me;

   me = this_object();

   announce (me, "��ׯ���˲ι�Ʒ��������ڿ�ʼ��\n");
   set_temp("ready2", 1);
}

string asked_guo(object me)
{ 
	int i, total;
	object guo;
	object *inv ;
      
	me=this_player();

	//if no renshenguo party at all...
	if( query_temp("ready0") != 1 ) return ("�˲ι����Ǹ��ö�����\n");

	//if not in the right place, no guo...
	//need the right name, also right outdoors(so ppls can not use fake room).
	if( (environment(this_object()))->query("short") != "�˲ι�԰" || 
		(environment(this_object()))->query("outdoors") != "wuzhuang" )
	{
		return ("�����ֲ��ǹ�԰���������˲ι���\n");
	}
        if( userp(me) && (!wizardp(me))  )
           { 
           	if(query_temp("give_num")<3&&me->query_temp("give_rsg")!=1)
           	  {
           	    me->set_temp("give_rsg",1);
                    add_temp("give_num",1);
                  }  
           }  
	
	//if waiting for ppls...
	if( query_temp("ready1") != 1 ) return ("��Ҫ�����ٵȵȡ�\n");
        
         //if ready to begin...
        if( query_temp("ready2") != 1 ) return ("��Ҫ�������Ͼ��С�\n");

        if( query_temp("give_num") < 3 ) return ("��Ҫ�����ٵȵȡ�\n");
	
	//if finished...
	if( query_temp("finished") == 1 ) return ("�˲ι��ѷַ����ˡ�\n");

	//now check how many people here...
	total = 0;
	inv = all_inventory( environment(this_object()) );
	for(i=0; i<sizeof(inv); i++)
	{
		if( inv[i]->query_temp("give_rsg")==1 )
	  	 {
	  	   guo = new("/d/obj/drug/renshen-guo");
		   guo->move(inv[i]);
	  	   message_vision("$N��$nһö�˲ι���\n", this_object(), inv[i]);
		   announce (this_object(), "��ϲ��ϲ��" + inv[i]->query("name") + "����˲ι�һö��\n");
		   inv[i]->delete_temp("give_rsg");
		 }
	}	 
		
		set_temp("finished", 1);
		call_out("finishing", 10);

		return ("�ã��˲ι��ַ���ϣ���λ���;������ðɡ�\n");
	
	
}


void finishing()
{
   message_vision("$N������Ц��������ʱ��Ӱ�����ˡ�\n", this_object());
   delete_temp("invite");//this is necessary if not going to destruct this obj.
   destruct(this_object());
}

void inviting (object me)
{
   int i;
   object *list;

   if (! me->query_temp("invite"))
   return;
  
   remove_call_out ("inviting");
   call_out ("inviting",4+random(4),me);

   list = users();
   i = sizeof(list);
   while  (i--)
   {
     string here, there;

     reset_eval_cost();
    
     if (!environment(list[i]))
        continue;
    
     if (environment(list[i])->query("unit")) // not a room
        continue;
   
     if (list[i]->is_fighting())
        continue;
    
     if (list[i]->is_busy())
        continue;
    
     if (list[i]->query_temp("no_move"))
        continue;
    
     if (!living(list[i]))
        continue;
    
     if ((string)list[i]->query_temp("accept")!=me->query("id"))
        continue;

     list[i]->set_temp("accept",0);
     here = (string)environment(me);
     there = (string)environment(list[i]);
     if (here == there)
        continue;

     message_vision("$N�Ĵ�������һ�֡�\n",me);
     list[i]->set_temp("accept",0);
     list[i]->set_temp("wzg/from",there);

     message_vision("һ������Ʈ�����������һֻ�޴�����佫$N����һ�֣���ʧ����ա�\n",list[i]);
         list[i]->move(here);
     message_vision("��$N��������һ����$n���˳�����\n",me,list[i]);
     break;
   }
}

int do_back(string arg)
{
   object who = this_player();
   object me = this_object();
   string here = (string)environment(me);
   string there = who->query_temp("wzg/from");

   message_vision("$N����$n��$N�ط���\n",who,me);
 
    //if (!there)
   // there = "/d/city/kezhan";
   there = "/d/city/kezhan";

   who->set_temp("accept",0);
   message_vision("$N�Ĵ��䳯��$n����һ�֡�\n",me,who);
   who->move(there);
   message_vision("���������һֻ�޴����������һ����ֻ��$N�����滬�˳�����\n",who);
  
   return 1;
}
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

int give_fu(object ob)
{
        object who, me;
        who=this_player();
        me=this_object();
        if( (string)who->query("family/family_name")!="��ׯ��" ) {
                message_vision("$Nбб�����$nһ�ۣ�˵���˲���Ϊ���˵�Ҳ��\n", me, who);
                return 1;
        }
if ((int)who->query("combat_exp") < 300000||who->query_skill("taiyi",1)<61)
                 {  message_vision("$Nбб�����$nһ�ۣ�˵����᲻�������Ű��ԣ�\n", me, who);
                       return 1;}
       if ((int)who->query("faith") < 500) {
           message_vision("$N��ݺݵؿ���$nһ�ۣ�˵����Ϊ���ɳ�����������\n", me, who);
                       return 1;}
	if ((int)me->query("number") >= 1)
          { write("��Ԫ���ɰ���һ�죬�����̫���ˣ���������˵�ɣ�\n");
          return 1;
}
                ob=new("/d/obj/misc/baguafu.c");
                ob->move(who);
		me->add("number",1);
		message_vision("$N�ó��ŷ�ֽ��������ŤŤ���˼����֣�������$n��\n", me, who);
                return 1;
}


int begin_go()
{
	object me,ob,jin,pan;
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
    if (me->query("guanli/wzg"))
	  return 0;
    
		if (me->query("fangcun/panlong_wzg")=="done")
	{
        message_vision(HIW"\n��Ԫ���ɵ�����Ȼ"+RANK_D->query_respect(me)+ "����,�Ϸ���Ͷ���\n"NOR,me);
        message_vision(HIY"\n\n��Ԫ������Ȼ�����������Ƕ���ȥ��\n"NOR,me);
		ob->move("/d/lingtai/inside1");
        return 1;
	}
	    if ((me->query("fangcun/panlong_wzg_baxian")=="done")&&(me->query("fangcun/panlong_wzg_rsg")=="done"))
	{
		me->add("fangcun/panlong_visite",1);
		me->set("fangcun/panlong_wzg","done");
		me->delete("fangcun/panlong_wzg_baxian");
		me->delete("fangcun/panlong_wzg_rsg");
       message("chat",HIC+"��"+HIW+"��������"+HIC+"����Ԫ����(Zhenyuan daxian)��"+me->query("name")+RANK_D->query_respect(me)+"���Ұ˸�ͽ����Ը��������̨�����Ϸ���������\n"NOR,users());
         message("chat",HIC+"��"+HIW+"��������"+HIC+"����Ԫ����(Zhenyuan daxian)��"+me->query("name")+"�õ�����������"+chinese_number(dx1)+"�꣬��ѧ"+wx+"�㣬Ǳ��30000�㣮\n"NOR,users());
   	    if (me->query("family/family_name")=="����ɽ���Ƕ�")
		   message_vision("\n��Ԫ����Ц��������֮�ջ���" + RANK_D->query_respect(me) + "����֪ͨ�Ϸ�һ��.\n"NOR,me);
		me->add("daoxing",dx);
		me->add("combat_exp",wx);
		me->add("potential",30000);
	    if ((me->query("family/family_name")!="����ɽ���Ƕ�")||(me->query("fangcun/panlong_noway")))
			me->set("guanli/wzg",1);
		return 1;
	}
	if ((me->query("fangcun/panlong_wzg_baxian")=="done")&&(me->query_temp("get_guo")))
	{
              command("hmm "+me->query("id"));
    		  command("say �ѵ�" + RANK_D->query_respect(me) + "��ȥ���˲ι�����\n");
			  return 1;
	}
	if (me->query("fangcun/panlong_wzg_baxian")=="done")
	{
	          command("haha "+me->query("id"));
    		  command("say " + RANK_D->query_respect(me) + "��������ͽ�����Ը��������Щ�����͸������ʦ���ᣬ" + RANK_D->query_respect(me) + "��ȥ�����˲ι����ϴ�"+HIY"����"+NOR""+CYN"��������\n");
   	  	      message_vision("\n��Ԫ����Ц�Ÿ�$Nһ�ѽ���Ӻ�һ�����̣�\n"NOR,me);
			  jin=new("/d/qujing/wuzhuang/obj/jinjizi");
			  jin->move(me);
			  pan=new("/d/qujing/wuzhuang/obj/danpan");
			  pan->move(me);
			  me->set_temp("get_guo",1);
			  return 1;
	}


    if (me->query("fangcun/panlong_wzg")!="begin")
    {
  command("say " + RANK_D->query_respect(me) + "�������ã����ǰ˸�ͽ���������֪��ô���������أ���ƽ����ܽ�
              ���ϼ���С�һﶼ����˵ʵ����" + RANK_D->query_respect(me) + "���ð��Ϸ�ȥ��������������ʲô���գ�\n");
   me->set("fangcun/panlong_wzg","begin");
        if ((me->query("family/family_name")!="����ɽ���Ƕ�")||(me->query("fangcun/panlong_noway")))
        	me->set_temp("wzg_baxian","go");
	return 1;
	}
  command("say ��Σ�" + RANK_D->query_respect(me) + "��������ʲô��\n\n");
  if ((me->query("family/family_name")!="����ɽ���Ƕ�")||(me->query("fangcun/panlong_noway")))
        	me->set_temp("wzg_baxian","go");
  return 1;
}
