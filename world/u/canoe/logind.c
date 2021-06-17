// logind.c

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <net/daemons.h>
#include <net/macros.h>
#include <mudlib.h>     // for GB_AND_BIG5 define.
#define FileName "/adm/daemons/UserNumber" // by canoe
inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
string *banned_name = ({
	"��", "��", "��", "��", "��", "��", "������", "��Сƽ", "����", "���Ż�",
	"�Լ�", "ĳ��", "ʬ��", "����","����", "����", "���","��",
	"�����", "ȥ���", "ë��", "��ʦ", "�����̵�",
});

string *default_name=({"����","����", "����", 
	               "����","�׳�","����","����",
		       "���","ư��","�ȳ�","��",
			"ţ", "�ϻ�", "����",
			"��","è��","��","��",
			"����","�ڹ�","��","���",
			"¹","��","Ϭţ"});
string *default_prefix=({"С","��","��","��","��","��","��","��",
	"ֽ","ľͷ","ʯͷ","��"});


void logind_user_log(); // mon 11/5/98
int total_count;
int howmany_user();
private void encoding(string arg, object ob);
private void if_young(string arg, object ob);
private void get_id(string arg, object ob);
private void confirm_id(string yn, object ob);
object make_body(object ob);
private void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
string dis_attr(int value);
private void confirm_gift(string yn,object ob,object user);
private void judge_freeze(object ob); //����ԭ�� �����ж��˺��Ƿ񱻶���
int do_counter(); // �ܹ���½����ͳ��
int check_legal_password(object ob,string arg); // ��֤���������

int howmany_user()
{
	int i,j,reg_cnt;
	string *dir , *ppls, name;
	mixed info;
	seteuid(getuid());
	reg_cnt=0;
	dir=get_dir(DATA_DIR+"login/");
	for(i=0; i<sizeof(dir);i++)	{
		reset_eval_cost();
		ppls=get_dir(DATA_DIR+"login/"+dir[i]+"/");
		reg_cnt+=sizeof(ppls);
	}
	return reg_cnt;
}
void create() 
{
	seteuid(getuid());
	set("channel_id", "���߾���");
        set("id", "logind");
}

// mon 11/7/98
void logind_user_log()
{
    int user=sizeof(users());
    int total;

    remove_call_out("logind_user_log");
    rm("/log/user_count");    log_file("user_count",""+
            ((total=total_count)?total:user)+"\n"+
            user+"\n"+
            UPTIME_CMD->report_str()+"\n"+
            "�������μ�\n");
    call_out("logind_user_log",600);
}

// added by snowcat Mar 11 1998


void logon(object ob)
{

#ifdef GB_AND_BIG5
    write("            �������λ�ӭ�����ã�ʹ�ù�������������룺gb\n");
    write("         Welcome to "BLINK HIY"DTXYJ!"NOR" Select GB or BIG5 (gb/big5):");
    input_to( (: encoding :), ob );
#else
    encoding("gb",ob);
#endif

}

private void encoding(string arg, object ob)
{
	object *usr;
	int i, ttl_cnt, wiz_cnt, ppl_cnt, login_cnt, max_online,avg_online;
	string ip_name, ip_number, online_num;
 	int ii;
        mixed info;
	int encode;
	

	if(!arg || arg=="") {
	    write("\nSelect ������ GB or �j���X BIG5 (gb/big5):");
	    input_to( (: encoding :), ob );
	    return;
	} else if(arg[0..0]=="g" || arg[0..0]=="G")
	    encode=0;
	else if(arg[0..0]=="b" || arg[0..0]=="B")
	    encode=1;
	else {
	    write("\nSelect ������ GB or �j���X BIG5 (gb/big5):");
	    input_to( (: encoding :), ob );
	    return;
	}
	
	ob->set_encoding(encode);

	ip_name = query_ip_name(ob);
	ip_number = query_ip_number(ob);



// snowcat dec 10 1997
// try strict ban here...weiqi.

	if ("/adm/daemons/band"->is_strict_banned(query_ip_number(ob)) == 1) {
write(HIR"���ĵ�ַ�ڱ� MUD ֮���������ƻ��ˡ�\n��E-MAIL:torrow0812@21cn.com������\n"NOR);
	   	destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, strict_banned\n"));
	   	return;
	}

	
	// try not accept "name" as IP

	if (!ip_name) {
		destruct(ob);
		log_file( "ALLCONT", sprintf("kicked out, No IP\n"));
		return;
	}

	for(ii=0; ii<sizeof(ip_number); ii++) {
		if( (ip_number[ii] != '.')&&(ip_number[ii]>'9') ){
			destruct(ob);
			log_file( "ALLCONT", sprintf("kicked out, Non_number\n"));
			return;
		}
	}
	
	write(CLR);
	cat(WELCOME);
	UPTIME_CMD->report();

	// children will show both netdead and interactive users.
	usr = children(USER_OB);
	wiz_cnt = 0;
	ppl_cnt = 0;
	login_cnt = 0;
	for(i=0; i<sizeof(usr); i++) {
		if( !environment(usr[i]) ) login_cnt++;
		else if( (wizardp(usr[i]) && (string)wizhood(usr[i])!="(elder)")&& !usr[i]->query("env/invisibility") ) wiz_cnt++;
		else ppl_cnt++;
	}
        max_online = atoi(read_file(__DIR__"maxonline",1));
	avg_online = atoi(read_file(__DIR__"avguser",1));
	if(ppl_cnt > max_online)
	   {
	   	online_num = sprintf("%d",ppl_cnt);
	   	write_file(__DIR__"maxonline",online_num,1);
	   }
printf("��������("HIY"��վ"NOR")����ע�����"HIR"%s"NOR"λ����"HIW"%s"NOR"�˴η��ʡ�\n",chinese_number(howmany_user()),chinese_number(do_counter()));
printf("��������("HIY"��վ"NOR")��վ���������������Ŀ��"HIY"%s"NOR" �ˣ�ƽ��������Ŀ��"HIY"%s"NOR" �ˡ�\n",chinese_number(max_online),chinese_number(avg_online));
	printf("Ŀǰ����"HIR"%s"NOR"λ������Ա��"HIC"%s"NOR"λ��ң��Լ�"HIG"%s"NOR"λʹ�����ڳ������ߡ�\n\n",
		chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) );
rm("/log/counter_for_web");
log_file("counter_for_web",sprintf("Ŀǰ����%sλ��ʦ��%sλ��������ϣ��Լ�%sλʹ���߳���������",
                chinese_number(wiz_cnt), chinese_number(ppl_cnt), chinese_number(login_cnt) ));
login_cnt = 0;
	// mon 11/7/98
	//check whether user_log still running.
	info = filter_array(call_out_info(), (: $1[1]=="logind_user_log" :));
	if(!sizeof(info)) logind_user_log();


      /* move this check to after user input id.
	 
// mon 4/19/98
// reduce number of pending login users.
#ifdef MAX_USERS
	if(sizeof(usr)>(MAX_USERS+10)) {
	    write("�Բ��𣬴������ε�����Ѿ�̫���ˣ�������������\n");
	    destruct(ob);
	    return;
	}
#endif

*/

	if (ob) ob->set_temp("id_count",0);
	//mon 10/15/97 to prevent flooding illegal ID after login.

#ifndef GB_AND_BIG5
#endif
        
	//we do not welcome young kid playing mud. weiqi...971220.
	write("����ѧ������Ҫ������ѧϰ������Ϸ����ӭ��Сѧ�����档\n");
	write("���Ƿ�����Сѧѧ���������С��(yes/no)");
	input_to( (: if_young :), ob );
}

private void if_young(string arg, object ob)
{
        int id_count;

        id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id.
        id_count++;
        ob->set_temp("id_count",id_count);
        if(id_count>3) {
          destruct(ob);
          log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
          return;
        }

        if(arg=="\n" || arg=="") {
	    write("���Ƿ�����Сѧѧ���������С��(yes/no)");
	    input_to( (: if_young :), ob );
	    return;
	}

	if( arg[0..0] == "y" || arg[0..0] == "Y" )
	{
		write("\n�ã��Ͻ�ȥѧϰ����������\n");
		destruct(ob);
		return;
	}

	if( arg[0..0] != "n" && arg[0..0] != "N" ) {
	    write("���Ƿ�����Сѧѧ���������С��(yes/no)");
	    input_to( (: if_young :), ob );
	    return;
	}

	cat(XYJ_SITES);
	write("\n����Ӣ�����֣������������� new ע�ᣩ");
	input_to( (: get_id :), ob);
}

private void get_id(string arg, object ob)
{
	object ppl, *usr = children(USER_OB);
        int id_count;

//edw 6/2/98
        int NowLogin, MaxLimit, login_site, i;
	string my_ip, new_ip;
//end edw

        if(!ob) return;

        id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id. 
        id_count++;
        ob->set_temp("id_count",id_count);
	if(id_count>6) {
	  destruct(ob);
          log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
	  return;
        }

	arg = lower_case(arg);
	if( !check_legal_id(arg)) {
		write("����Ӣ�����֣�");
		input_to("get_id", ob);
		return;
	}

	ppl = find_body(arg);

#ifdef MAX_USERS
	if( (string)SECURITY_D->get_status(arg)=="(player)"
	&& sizeof(users()) >= MAX_USERS ) {
		// Only allow reconnect an interactive player when MAX_USERS exceeded.
		// i.e., ppl exist. (has nothing to do with whether it interactive) -- mon 3/15/99
		//if( !ppl || !interactive(ppl) ) 
		if( !ppl ) {
		  write("�Բ��𣬴������ε�����Ѿ�̫���ˣ�������������\n");
		  destruct(ob);
		  return;
		} 
	}
#endif

	//if( wiz_level(arg) < wiz_lock_level ) {
		//write("�Բ���" + MUD_NAME + "Ŀǰ������ʦ�ȼ� " + WIZ_LOCK_LEVEL
			//+ " ���ϵ��˲������ߡ�\n");
		//destruct(ob);
		//return;
	//}
	
//edw@zju.mirror.xyj 6/2/98 (limit multi-login)
// MAX_LOGIN and LOGIN_SITE should be defined in login.h
#ifdef MAX_LOGIN
	
      if(!ppl) { // only check this for new login.
	         // allow existing players to reconnect.
      my_ip=query_ip_number(ob);

      MaxLimit="/adm/daemons/band"->allow_multi_login(my_ip);
      if(!MaxLimit) MaxLimit=MAX_LOGIN;
#ifdef LOGIN_SITE
      login_site=LOGIN_SITE;
#else
	  login_site=0;
#endif
      if(my_ip && login_site==0) // ignore the last field of the IP
	  my_ip=my_ip[0..strsrch(my_ip, ".", -1)];

      NowLogin=0;

      for(i=0;i<sizeof(usr);i++) 
        if(ob!=usr[i]) {
	    new_ip=query_ip_number(usr[i]);
	    
	    // for net_dead players.
	    if(!new_ip && !interactive(usr[i]))
		new_ip=usr[i]->query_temp("netdead_ip");

	    if(new_ip && login_site==0)
		new_ip=new_ip[0..strsrch(new_ip, ".", -1)];

            if(my_ip==new_ip) {
               NowLogin++;
	    }
			
	}

      if(NowLogin>=MaxLimit) {
	      write(sprintf("�Բ��𣬴����IP��ַ����ͬʱ��¼%sλ���\n",
		      chinese_number(MaxLimit+1)));
              destruct(ob);
              return;
       } 
      }
#endif

	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	if( arg=="guest" ) {
		// If guest, let them create the character.
//		confirm_id("Yes", ob);
//		return;
} else if (arg=="new") { // new player login
                write("\n�������Լ�ȡһ��Ӣ�����֣�");
		input_to("get_new_id",ob);
		return;
	} else if( file_size(ob->query_save_file() 
		    + __SAVE_EXTENSION__) >= 0 ) {
		if( ob->restore() ) {
			judge_freeze(ob);  
			write("\n����������(����������½����)��");
			input_to("get_passwd", 1, ob);
			return;
		}
		write("�������ﴢ�浵����һЩ���⣬�����ñ������֪ͨ��ʦ����\n");
		destruct(ob);
		return;
	} 
	
        write("û�������ң�����\n");
	write("����Ӣ�����֣������������� new ע�ᣩ");
	input_to("get_id", ob);
	return;
}
private void judge_freeze(object ob)
{
        int freeze_time;        
      freeze_time=ob->query("freeze_time");
        if( time() < freeze_time ) {            
write ("�Բ�������˺��Ѿ�������,����"+(freeze_time+3600-time())/3600 +"Сʱ����ʹ�á� \n");
             destruct(ob);
             return;
        }       
}                      

private void get_new_id(string arg, object ob)
{
object ppl, *body;  
   int id_count, i, nb=0;  
// edit by canoe
//�޸Ķ��ص�½

        if(!ob) return;

        id_count=ob->query_temp("id_count");
// mon 7/19/97 to prevent flooding by repeating illegal id. 
        id_count++;
        ob->set_temp("id_count",id_count);
	if(id_count>6) {
	  destruct(ob);
          log_file( "ALLCONT", sprintf("kicked out, illegal ID.\n"));
	  return;
        }

        if(!arg) {
                write("\n�������Լ�ȡһ��Ӣ�����֣�");
		input_to("get_new_id", ob);
		return;
        }

	arg = lower_case(arg);
	if( !check_legal_id(arg)) {
                write("\n�������Լ�ȡһ��Ӣ�����֣�");
		input_to("get_new_id", ob);
		return;
	}

	if( (string)ob->set("id", arg) != arg ) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	ppl = find_body(arg);
	if(ppl || arg=="guest" || arg=="new") {
	    write("��������Ѿ���������ʹ���ˣ�����");
            write("\n�������Լ�ȡһ��Ӣ�����֣�");
	    input_to("get_new_id",ob);
	    return;
	}

	if( file_size(ob->query_save_file() 
		    + __SAVE_EXTENSION__) >= 0 ) {
	    write("��������Ѿ���������ʹ���ˣ�����");
            write("\n�������Լ�ȡһ��Ӣ�����֣�");
	    input_to("get_new_id",ob);
	    return;
// edit by canoe
//�޸Ķ��ص�½����
	} 
        ob->set("new_player", 1);  
        body = children(LOGIN_OB);  
        i = sizeof(body);  
        while (i--) {   
          if( clonep(body[i]) && body[i]->query("id")==arg  
              && body[i]->query("new_player")==1 ) nb++;  
          if( nb>1 ) {  
              write("�Բ����Ѿ������������Ӣ�����ִ��������ˣ�����\n");  
              write("\n�������Լ�ȡһ��Ӣ�����֣�");  
              ob->delete("new_player");  
              input_to("get_new_id",ob);  
              return;  
           }  
        }  
// over

	confirm_id("Yes", ob);
	return;
}

private void get_passwd(string pass, object ob)
{
	string my_pass,id;
	object user;
        // by canoe �޸�˫�������½Ч��
        int pwdflag=0; 
        write("\n");
	my_pass = ob->query("password");
	
	if( crypt(pass, my_pass) == my_pass)
	{
	write(HIY"\n��ʹ���˵�½����ɹ���½��\n"NOR);
	pwdflag=1;
	} 
	my_pass=ob->query("super_password");
	if(!pwdflag
	&&crypt(pass, my_pass) ==my_pass )
	{
	write(HIR"\n��ʹ���˹�������ɹ���½��\n���ǽ�����ֻ�������뱻��������²�ʹ�ù��������½��\n"NOR);
	pwdflag=1;
	}
	if(!pwdflag
	||!SECURITY_D->match_wiz_site(ob, query_ip_number(ob)) )
	 {
		write("�������");
		write("���������ߣ�������ȷ���������ȡһ���µ�Ӣ�����֡�\n");
		if((id=ob->query("id")) && member_array(id,
			SECURITY_D->get_wizlist())!=-1)
		  log_file("wizlogin",ctime(time())+" "+id+
			" failed login from "+query_ip_number(ob)+"\n");
		else
		  log_file("login",ctime(time())+" "+id+
			" failed login from "+query_ip_number(ob)+"\n");
		destruct(ob);
		return;
	}
	// end
	// by canoe �޸�kickout��½ʱ������
	if(time()-(int)ob->query("kickout_time") < 600)
			{
			write("������û�н��롼�������Ρ���Ȩ������ʮ���Ӻ������ߡ�\n");
			destruct(ob);
			return;
			}
	// end
	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {
	    
	    // netdead is delayed being set
	    // after disconnected, so should use interactive.
	    // mon 7/5/98
		if( !interactive(user) ) {
			reconnect(ob, user);
			return;
		}
		write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}

   if( objectp(user = make_body(ob)) ) {
     if( user->restore() ) {
        log_file( "USAGE", sprintf("%s(%s) loggined from %s (%s)\n", user->query("name"),
          user->query("id"), query_ip_number(ob), ctime(time()) ) );

       enter_world(ob, user,0);
        return;
     } else {
        destruct(user);
     }
   }
   write("�������´���������\n");
   confirm_id("y", ob);
}


private void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if( yn=="" ) {
		write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)");
		input_to("confirm_relogin", ob, user);
		return;
	}	

	if( (yn[0]!='y' && yn[0]!='Y') || !user ) {
	    // user may be destructed during the process.
	    // so I put in this check. mon 4/15/98
		write("�ðɣ���ӭ�´�������\n");
		destruct(ob);
		return;
	} else {
		tell_object(user, "���˴ӱ�( " + query_ip_number(ob)
			+ " )����ȡ���������Ƶ����\n");
		log_file( "USAGE", sprintf("%s(%s) replaced by %s (%s)\n",
		user->query("name"), user->query("id"),
			query_ip_number(ob), ctime(time()) ) );
	}

	// Kick out tho old player.
	old_link = user->query_temp("link_ob");

//	if( old_link ) {
	// mon 7/5/98
	// need to check user is interactive before exec.
	// user may become non-interactive after the input_to.
	if( old_link && interactive(user)) {
	        // 5/11/98 mon
	        user->set_encoding(ob->query_encoding());

		exec(old_link, user);
	}
	if(old_link)      // mon 9/14/98
		destruct(old_link);

	reconnect(ob, user);	
}

private void confirm_id(string yn, object ob)
{
    /*
	if( yn=="" ) {
		write("ʹ��������ֽ��ᴴ��һ���µ������ȷ����(y/n)��");
		input_to("confirm_id", ob);
		return;
	}	

	if( yn[0]!='y' && yn[0]!='Y' ) {
		write("�ðɣ���ô��������������Ӣ�����֣�");
		input_to("get_id", ob);
		return;
	}
	*/


	write( @TEXT

�������Լ���һ�����ϡ��������Ρ���������������֡���
�����ֽ��������ڴ��������е�����������󽫲����ٸ��ġ�
�벻ҪȡһЩ���Ż�����������������ŵ����֡�

TEXT
	);
	write("�����������֣�");
	ob->set_temp("get_name",0);
	input_to("get_name", ob);
}

private void get_name(string arg, object ob)
{
        arg = CONVERT_D->input(arg,ob);

	if( !check_legal_name(arg) ) {
            ob->add_temp("get_name",1);
	    if(ob->query_temp("get_name")>2) {
	        // the user can't input proper chinese name.
	        // assign one for him/her.    mon 4/19/98

		arg=default_prefix[random(sizeof(default_prefix))]+
		    default_name[random(sizeof(default_name))];

		write("��Ϊ�㲻�������ʵ����������֣�ϵͳָ���������Ϊ��"+
			arg+"\n");
		write("���ڽ�����Ϸ������ʦ�����޸ġ�\n");

	    } else {
		write("�����������֣�");
		input_to("get_name", ob);
		return;
	    }
	}
// by canoe for suppwd
	printf("%O\n", ob);
	ob->set("name", arg);
	write(HIG"\nע�⣺��������޸ġ��������ݡ���ɱ����Ҫ�������룻\n\n"NOR);
	write(HIR"      һ������²�����ģ���������Ʊ��档\n\n"NOR);
	write(HIY"���趨���Ĺ������룺"NOR);
	input_to("get_super_password", 1, ob);
}

private void get_super_password(string pass, object ob)
{
	write("\n");
	if( !check_legal_password(ob,pass)) {
		write(HIW"�������趨�������룺");
              	input_to("get_super_password", 1, ob);
		return;
	}
	ob->set("super_password", crypt(pass,0) );
	write(HIR"��������һ�����Ĺ������룬��ȷ����û�Ǵ�"NOR);
	input_to("confirm_super_password", 1, ob);
}
private void confirm_super_password(string pass, object ob)
{
	string old_pass;
	write("\n");
	old_pass = ob->query("super_password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write(HIY"����������Ĺ������벢��һ�����������趨һ�ι������룺"NOR);
		input_to("get_super_password", 1, ob);
		return;
	}
	write(HIC"��Ϸ��½������ָ��ÿ�ν�����Ϸʱ������������롣\n\n"NOR);
	write(HIG"���趨������Ϸ��½���룺"NOR);
	input_to("new_password", 1, ob);
}
// end
private void new_password(string pass, object ob)
{
	write("\n");
	if( strlen(pass)<5 ) {
		write("��������Ҫ������ַ���ɣ��������������룺");
		input_to("new_password", 1, ob);
		return;
	}
	if( crypt(pass, ob->query("super_password"))==ob->query("super_password") ) {
		write("���ĵ�½���벻�ܺ͹�������һ�����������������룺");
		input_to("new_password", 1, ob);
		return;
	}
	ob->set("password", crypt(pass,0) );
	write(HIY"��������һ���������룬��ȷ����û�Ǵ�"NOR);
	input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
	string old_pass;
	write("\n");
	old_pass = ob->query("password");
	if( crypt(pass, old_pass)!=old_pass ) {
		write("��������������벢��һ�����������趨һ�ε�½���룺");
		input_to("new_password", 1, ob);
		return;
	}

	write("���ĵ����ʼ���ַ��");
	input_to("get_email",  ob);
}

private void get_email(string email, object ob)
{
	object user;
        // By Canoe ǿ��emailһ��Ҫ������ȷ
        string id,addr;
        write("\n");
         if (email=="" || strsrch(email,".")==-1 
        || sscanf(email,"%s@%s",id,addr) !=2)
        {
		write(HIC"�����ʼ���ַ��Ҫ�� id@dtxy.net �ĸ�ʽ��\n");
		write(HIW"���ĵ����ʼ���ַ��"NOR);
		input_to("get_email", ob);
		return;
	}
	ob->set("email", email);
	//end
	
	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	ob->set("body", USER_OB);
	if( !objectp(user = make_body(ob)) ) {
	    if(ob) destruct(ob);
	    return;
	}

	write("��Ҫ��������(m)�Ľ�ɫ��Ů��(f)�Ľ�ɫ��");
	input_to("get_gender", ob, user);
}

private void get_gender(string gender, object ob, object user)
{
	if( gender=="" ) {
		write("��Ҫ��������(m)�Ľ�ɫ��Ů��(f)�Ľ�ɫ��");
		input_to("get_gender", ob, user);
		return;
	}

	if( gender[0]=='m' || gender[0]=='M' )
		user->set("gender", "����");
	else if( gender[0]=='f' || gender[0]=='F' )
		user->set("gender", "Ů��" );
	else {
		write("�Բ�����ֻ��ѡ������(m)��Ů��(f)�Ľ�ɫ��");
		input_to("get_gender", ob, user);
		return;
	}
	
        confirm_gift("n",ob,user);
}

object make_body(object ob)
{
	string err;
	object user;
	int n;

        if(!ob->query("body")) {
	  return 0;
        }
	user = new(ob->query("body"));
	if(!user) {
		write("���ڿ������������޸��������ĳ�ʽ���޷����и��ơ�\n");
		write(err+"\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set("id", ob->query("id"));
	user->set_name( ob->query("name"), ({ ob->query("id")}) );
	return user;
}

private void confirm_gift(string yn, object ob, object user)
{
        int n, a, b;

	if(!ob || !user) {
            if(user) {
	      destruct(user);
	      return;
	    }
            if(ob) destruct(ob);
	    return;
        }

        user->set("kar", 20 );
	user->set("str", 20 );
	user->set("cps", 20 );
	user->set("int", 25 );
	user->set("cor", 20 );
	user->set("con", 20 );
	user->set("spi", 25 );
	user->set("per", 20 );

	// mon 3/21/99 allow players to choose gift after login.
	user->set("no_gift",1);

	    CHAR_D->setup_char(user); //setup user weight. mon 11/7/97
	    user->set("title", "��������");
	    user->set("birthday", time() );
	    user->set("potential", 99);
	    user->set("food", user->max_food_capacity());
	    user->set("water", user->max_water_capacity());
	    user->set("channels", ({ "chat","rumor","xyj","sldh","es" }) );
	    log_file( "USAGE", sprintf("%s was created from %s (%s)\n", user->query("id"),
		query_ip_number(ob), ctime(time()) ) );

	    ob->set("last_from",query_ip_number(ob));
	    ob->set("last_on",time());
// edit by canoe
//�޸Ķ��ص�½����
ob->delete("new_player");  
//over

 return enter_world(ob, user,0);
}

string dis_attr(int value)
{       int gift=20;
        if( value > gift ) return sprintf( HIY "%3d" NOR, value );
        else if( value < gift ) return sprintf( CYN "%3d" NOR, value );
        else return sprintf("%3d", value);
}

varargs void enter_world(object ob, object user, int silent)
{
	object cloth, room, mbx;
	string startroom="";
	string ip_from;
	int num;
        ////////////
	// Add for ����֪ͨ By Canoe 2001.03.29
       int qqnum;
       string *qqfriends;
       object qqob;
       ////////////////

        reset_eval_cost();
        user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);

	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());

	exec(user, ob);

	write("\nĿǰȨ�ޣ�" + wizhood(user) + "\n");
	user->setup();

	// In case of new player, we save them here right aftre setup 
	// compeleted.
	user->save();
	ob->save();

        if( !silent ) {
	     if(file_size(MOTD)>0)
             user->start_more(read_file(MOTD));
		
	     // mon 3/21/99 
	     // new user login.
             if(user->query("no_gift")) {
	       user->move("/d/wiz/init",1);
	     } else {
		if( user->is_ghost() )
			startroom = DEATH_ROOM;
		else if( strlen(startroom = user->query("startroom"))<2 )
			startroom = START_ROOM;

                if(!wizardp(user) && startroom[0..2]=="/u/") {
		  startroom = START_ROOM;
                  user->set("startroom",startroom);
                }
                //added by mon 10/27/97

		// the following 7 lines are aded by snowcat dec 10 1997
		if (("/adm/daemons/band"
		    ->create_char_banned(query_ip_number(user)) == 1 ||
	    	    "/adm/daemons/band"->is_banned(query_ip_number(user))
		    == 1) && !wizardp(user)) {
			user->move("/d/wiz/guest");
			log_file( "ALLCONT", sprintf("from banned site\n"));
		}
		else if( !catch(load_object(startroom)) )
			user->move(startroom);
		else {
			user->move(START_ROOM);
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
		// by canoe �޸Ķ���ƷʱͻȻquit���ܽ�mud Bug
		if(!environment(user))
		       {
		       	user->move(START_ROOM);
			startroom = START_ROOM;
			user->set("startroom", START_ROOM);
		}
		// end
				if(!wizardp(user) || !user->query("env/invisibility"))
		tell_room(startroom, user->query("name") + "���߽���������硣\n",
			({user}));
	     }
	        if(file_size("/log/notice")>0){
			write(CYN"     �ԡԡԡԡԡԡԡԡԡԡԡ�"HIR"������������֪ͨ"NOR CYN"�ԡԡԡԡԡԡԡԡԡԡԡ�\n");
          		write("     "+read_file("/log/notice"));
   	  		write(CYN"     �ԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡԡ�\n"NOR);        }
   		mbx=ob->query_temp("mbox_ob");
		if (!mbx) {
		  mbx=new(MAILBOX_OB);
		  mbx->set_owner(ob->query("id"));
                }
		num=mbx->query_new_mail();
		if( num>0 ) {
	          write( GRN + "\nǧ���۸����㣺����"
		    +chinese_number(num)+
		    "���ţ��뵽�ϳǿ�ջ��һ�ˣ�����\n\n" + NOR);
		}
		destruct(mbx);
	      	ip_from="/adm/daemons/ipd"->seek_ip_address(query_ip_number(user));
// add by canoe 2001-06-17
// wiz����֪ͨ
   CHANNEL_D->do_channel( this_object(),wizardp(user)?"wiz":"sys",sprintf(NOR WHT "%s�� " HIG "%s" NOR WHT "���߽���,IP���ԣ�"HIG"%s"NOR,user->name()+"("+capitalize(user->query("id")) + ")", query_ip_number(user), ip_from)); 
// over ����֪ͨ
		}

	UPDATE_D->check_user(user, 0);
	TOPTEN_D->topten_checkplayer(user);
     //////////////////////////////////////////////////////
     // Add for QQ����֪ͨ By Canoe 2001.03.29
	if(mapp(user->query("qq"))
	   && sizeof(user->query("qq"))!=0
	   &&!user->query("env/invisibility")) {
	qqfriends = keys(user->query("qq"));
	 for(qqnum=0;qqnum<sizeof(qqfriends);qqnum++)
                {
				qqob=find_player(qqfriends[qqnum]);
				tell_object(qqob,BLINK HIG+"������ʹ֪ͨ������ĺ���"+user->query("name")+"["+capitalize(user->query("id"))+"]�����ˣ���\n"+NOR);
		}
         }
     ////////////////////////////////////////////////////////

      {
      	object caishen;
	if(objectp(caishen=find_object("/d/wiz/npc/caishen"))) {
	  caishen->check_one(user);
        }
      }
    // by canoe
    //  "/cmds/std/news"->check_news(user); // by canoe �޸���������֪ͨ 
    // end
}

varargs void reconnect(object ob, object user, int silent)
{
        object old_link;
	
	// mon 9/15/98
	old_link=user->query_temp("link_ob");
	if(old_link && old_link!=ob)
	    destruct(old_link);

	user->set_temp("link_ob", ob);
        ob->set_temp("body_ob", user);
  
	// 5/11/98 mon
	user->set_encoding(ob->query_encoding());

	exec(user, ob);

	user->reconnect();
	if( !silent && !user->query("env/invisibility")) {
		tell_room(environment(user), user->query("name") + "�������߻ص�������硣\n",
		({user}));
		// By canoe ,wiz��½ͨ��
		CHANNEL_D->do_channel( this_object(),(wizardp(user)?"wiz" :"sys"),
			sprintf("%s��%s�������߽��롣", user->query("name")+"(" + capitalize(user->query("id")) + ")", query_ip_name(user)) );
	        // end
	}
	UPDATE_D->check_user(user, 1); // this is for reconnect.
}

int check_legal_id(string id)
{
	int i;
	string *legalid;

	i = strlen(id);
	
	if( (strlen(id) < 3) || (strlen(id) > 8 ) ) {
		write("�Բ������Ӣ�����ֱ����� 3 �� 8 ��Ӣ����ĸ��\n");
		return 0;
	}
	while(i--)
		if( id[i]<'a' || id[i]>'z' ) {
			write("�Բ������Ӣ������ֻ����Ӣ����ĸ��\n");
			return 0;
		}
	legalid = explode(read_file(BANNED_ID), "\n");
	for(i=0; i<sizeof(legalid); i++)   {
	   if( id == legalid[i] )   {
		  write("�Բ����������ֻ���������˵����š�\n");
		  return 0;
       }
	}
	return 1;
}

int check_legal_name(string name)
{
	int i;

	i = strlen(name);
	
	if( (strlen(name) < 2) || (strlen(name) > 12 ) ) {
		write("�Բ�������������ֱ�����һ�����������֡�\n");
		return 0;
	}
	while(i--) {
		if( name[i]<=' ' ) {
			write("�Բ�������������ֲ����ÿ����ַ���\n");
			return 0;
		}
		if( i%2==0 && !is_chinese(name[i..<0]) ) {
			write("�Բ��������á����ġ�ȡ���֡�\n");
			return 0;
		}
	}
	if( member_array(name, banned_name)!=-1 ) {
		write("�Բ����������ֻ���������˵����š�\n");
		return 0;
	}

	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	for(int i=0; i<sizeof(body); i++) {
          ob=body[i];
	  if( clonep(ob) && getuid(ob) == name 
            && ob->query("max_gin")>0 ) return ob;
	    //check max_gin to avoid damaged user object.
        }

	return 0;
}

int set_wizlock(int level)
{
	if( wiz_level(this_player(1)) <= level )
		return 0;
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;
	wiz_lock_level = level;
	return 1;
}
// by canoe
int do_counter()
{       
	int number;
	string file;
	file = read_file(FileName);
	sscanf(file,"%d",number);
	number++;
	file=sprintf("%d",number);
	write_file(FileName,file,1);
	return number;
}
int check_legal_password(object ob,string pass)
{
        int i;
	int bigletter=0;
	int smlletter=0;
	int number=0;
	string id;
        i = strlen(pass);
        if( strlen(pass) <= 6)   {
                write(WHT"�Բ�����Ĺ���������������߸��ַ���\n");
                return 0;
        }
	id= ob->query("id");	
	if ( strsrch(id, pass) != -1 || strsrch(pass,id) != -1)
	{
	write(WHT"�Բ�����Ĺ�����������Ӣ������̫���ˡ�\n"NOR);
                return 0;
        }

        while(i--) {
                if( pass[i]<='Z' && pass[i] >='A' ) bigletter++;
		if( pass[i]<='z' && pass[i] >='a' ) smlletter++;

        }
	if( bigletter == 0 || smlletter == 0 || 
	bigletter+smlletter == strlen(pass))
{
        write(WHT"���Ĺ���������������д" + RED"��" + WHT"СдӢ����ĸ"
		+ RED"��" + WHT"����������ţ����֣���㣩��\n"NOR);
	return 0;
}
        return 1;
//end
}
