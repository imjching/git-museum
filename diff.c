int diff_rename_limit_default = -1;

int git_diff_config(const char *var, const char *value)
{
	if (!strcmp(var, "diff.renamelimit")) {
		diff_rename_limit_default = git_config_int(var, value);
		return 0;
	}

	return git_default_config(var, value);
}

static char *quote_one(const char *str)
{
	int needlen;
	char *xp;

	if (!str)
		return NULL;
	needlen = quote_c_style(str, NULL, NULL, 0);
	if (!needlen)
		return strdup(str);
	xp = xmalloc(needlen + 1);
	quote_c_style(str, xp, NULL, 0);
	return xp;
}

static char *quote_two(const char *one, const char *two)
{
	int need_one = quote_c_style(one, NULL, NULL, 1);
	int need_two = quote_c_style(two, NULL, NULL, 1);
	char *xp;

	if (need_one + need_two) {
		if (!need_one) need_one = strlen(one);
		if (!need_two) need_one = strlen(two);

		xp = xmalloc(need_one + need_two + 3);
		xp[0] = '"';
		quote_c_style(one, xp + 1, NULL, 1);
		quote_c_style(two, xp + need_one + 1, NULL, 1);
		strcpy(xp + need_one + need_two + 1, "\"");
		return xp;
	}
	need_one = strlen(one);
	need_two = strlen(two);
	xp = xmalloc(need_one + need_two + 1);
	strcpy(xp, one);
	strcpy(xp + need_one, two);
	return xp;
}

	const char *env_diff_opts;
	external_diff_cmd = getenv("GIT_EXTERNAL_DIFF");
	env_diff_opts = getenv("GIT_DIFF_OPTS");
	if (env_diff_opts) diff_opts = env_diff_opts;
#define TEMPFILE_PATH_LEN		50

	char tmp_path[TEMPFILE_PATH_LEN];
	const char *const diff_cmd = "diff -L%s -L%s";
	const char *const diff_arg  = "-- %s %s||:"; /* "||:" is to return 0 */
	const char *label_path[2];
	/* diff_cmd and diff_arg have 4 %s in total which makes
	 * the sum of these strings 8 bytes larger than required.
	 * terminating NUL; we used to subtract 5 here, but we do not
	 * care about small leaks in this subprocess that is about
	 * to exec "diff" anymore.
	cmd_size = (strlen(diff_cmd) + strlen(diff_opts) + strlen(diff_arg)
		    + 128);

		if (!strcmp(temp[i].name, "/dev/null"))
			label_path[i] = "/dev/null";
		else if (!i)
			label_path[i] = sq_quote(quote_two("a/", name_a));
		else
			label_path[i] = sq_quote(quote_two("b/", name_b));
		cmd_size += (strlen(label_path[i]) + strlen(input_name_sq[i]));
			    diff_cmd, label_path[0], label_path[1]);
	printf("diff --git %s %s\n",
	       quote_two("a/", name_a), quote_two("b/", name_b));
	if (label_path[0][0] == '/') {
		/* dev/null */
	else if (label_path[1][0] == '/') {

	memset(spec, 0, sizeof(*spec));
	memcpy(spec->path, path, namelen+1);
		if (s->data == MAP_FAILED)
			goto err_empty;
		s->should_munmap = 1;
			   const unsigned char *sha1,
	fd = git_mkstemp(temp->tmp_path, TEMPFILE_PATH_LEN, ".diff_XXXXXX");
	const char *othername;
	othername = (other? other : name);
		prepare_temp_file(othername, &temp[1], two);
			builtin_diff(name, othername, temp, xfrm_msg,
static void diff_fill_sha1_info(struct diff_filespec *one)
{
	if (DIFF_FILE_VALID(one)) {
		if (!one->sha1_valid) {
			struct stat st;
			if (stat(one->path, &st) < 0)
				die("stat %s", one->path);
			if (index_path(one->sha1, one->path, &st, 0))
				die("cannot hash %s\n", one->path);
		}
	}
	else
		memset(one->sha1, 0, 20);
}

static void run_diff(struct diff_filepair *p, struct diff_options *o)
	char msg[PATH_MAX*2+300], *xfrm_msg;
	char *name_munged, *other_munged;
	int len;
	name_munged = quote_one(name);
	other_munged = quote_one(other);

	diff_fill_sha1_info(one);
	diff_fill_sha1_info(two);

	len = 0;
	case DIFF_STATUS_COPIED:
		len += snprintf(msg + len, sizeof(msg) - len,
				"similarity index %d%%\n"
				"copy from %s\n"
				"copy to %s\n",
				(int)(0.5 + p->score * 100.0/MAX_SCORE),
				name_munged, other_munged);
	case DIFF_STATUS_RENAMED:
		len += snprintf(msg + len, sizeof(msg) - len,
				"similarity index %d%%\n"
				"rename from %s\n"
				"rename to %s\n",
				(int)(0.5 + p->score * 100.0/MAX_SCORE),
				name_munged, other_munged);
	case DIFF_STATUS_MODIFIED:
			len += snprintf(msg + len, sizeof(msg) - len,
					"dissimilarity index %d%%\n",
					(int)(0.5 + p->score *
					      100.0/MAX_SCORE));
		/* nothing */
		;
	}

	if (memcmp(one->sha1, two->sha1, 20)) {
		char one_sha1[41];
		int abbrev = o->full_index ? 40 : DIFF_DEFAULT_INDEX_ABBREV;
		memcpy(one_sha1, sha1_to_hex(one->sha1), 41);

		len += snprintf(msg + len, sizeof(msg) - len,
				"index %.*s..%.*s",
				abbrev, one_sha1, abbrev,
				sha1_to_hex(two->sha1));
		if (one->mode == two->mode)
			len += snprintf(msg + len, sizeof(msg) - len,
					" %06o", one->mode);
		len += snprintf(msg + len, sizeof(msg) - len, "\n");
	if (len)
		msg[--len] = 0;
	xfrm_msg = len ? msg : NULL;


	free(name_munged);
	free(other_munged);
}

void diff_setup(struct diff_options *options)
{
	memset(options, 0, sizeof(*options));
	options->output_format = DIFF_FORMAT_RAW;
	options->line_termination = '\n';
	options->break_opt = -1;
	options->rename_limit = -1;

	options->change = diff_change;
	options->add_remove = diff_addremove;
int diff_setup_done(struct diff_options *options)
	if ((options->find_copies_harder &&
	     options->detect_rename != DIFF_DETECT_COPY) ||
	    (0 <= options->rename_limit && !options->detect_rename))
		return -1;
	if (options->detect_rename && options->rename_limit < 0)
		options->rename_limit = diff_rename_limit_default;
	if (options->setup & DIFF_SETUP_USE_CACHE) {
	if (options->setup & DIFF_SETUP_USE_SIZE_CACHE)
	if (options->abbrev <= 0 || 40 < options->abbrev)
		options->abbrev = 40; /* full */

	return 0;
}

int diff_opt_parse(struct diff_options *options, const char **av, int ac)
{
	const char *arg = av[0];
	if (!strcmp(arg, "-p") || !strcmp(arg, "-u"))
		options->output_format = DIFF_FORMAT_PATCH;
	else if (!strcmp(arg, "-z"))
		options->line_termination = 0;
	else if (!strncmp(arg, "-l", 2))
		options->rename_limit = strtoul(arg+2, NULL, 10);
	else if (!strcmp(arg, "--full-index"))
		options->full_index = 1;
	else if (!strcmp(arg, "--name-only"))
		options->output_format = DIFF_FORMAT_NAME;
	else if (!strcmp(arg, "--name-status"))
		options->output_format = DIFF_FORMAT_NAME_STATUS;
	else if (!strcmp(arg, "-R"))
		options->reverse_diff = 1;
	else if (!strncmp(arg, "-S", 2))
		options->pickaxe = arg + 2;
	else if (!strcmp(arg, "-s"))
		options->output_format = DIFF_FORMAT_NO_OUTPUT;
	else if (!strncmp(arg, "-O", 2))
		options->orderfile = arg + 2;
	else if (!strncmp(arg, "--diff-filter=", 14))
		options->filter = arg + 14;
	else if (!strcmp(arg, "--pickaxe-all"))
		options->pickaxe_opts = DIFF_PICKAXE_ALL;
	else if (!strncmp(arg, "-B", 2)) {
		if ((options->break_opt =
		     diff_scoreopt_parse(arg)) == -1)
			return -1;
	}
	else if (!strncmp(arg, "-M", 2)) {
		if ((options->rename_score =
		     diff_scoreopt_parse(arg)) == -1)
			return -1;
		options->detect_rename = DIFF_DETECT_RENAME;
	}
	else if (!strncmp(arg, "-C", 2)) {
		if ((options->rename_score =
		     diff_scoreopt_parse(arg)) == -1)
			return -1;
		options->detect_rename = DIFF_DETECT_COPY;
	}
	else if (!strcmp(arg, "--find-copies-harder"))
		options->find_copies_harder = 1;
	else if (!strcmp(arg, "--abbrev"))
		options->abbrev = DIFF_DEFAULT_ABBREV;
	else if (!strncmp(arg, "--abbrev=", 9))
		options->abbrev = strtoul(arg + 9, NULL, 10);
	else
		return 0;
	return 1;
	unsigned long num, scale;
	int ch, dot;
	num = 0;
	dot = 0;
	for(;;) {
		ch = *cp;
		if ( !dot && ch == '.' ) {
			scale = 1;
			dot = 1;
		} else if ( ch == '%' ) {
			scale = dot ? scale*100 : 100;
			cp++;	/* % is always at the end */
			break;
		} else if ( ch >= '0' && ch <= '9' ) {
			if ( scale < 100000 ) {
				scale *= 10;
				num = (num*10) + (ch-'0');
			}
		} else {
			break;
		cp++;
	return (num >= scale) ? MAX_SCORE : (MAX_SCORE * num / scale);
	if (queue)
		diff_q(queue, dp);
	free(p->one);
	free(p->two);
/* This is different from find_unique_abbrev() in that
 * it needs to deal with 0{40} SHA1.
 */
const char *diff_unique_abbrev(const unsigned char *sha1, int len)
{
	int abblen;
	const char *abbrev;
	if (len == 40)
		return sha1_to_hex(sha1);

	abbrev = find_unique_abbrev(sha1, len);
	if (!abbrev) {
		if (!memcmp(sha1, null_sha1, 20)) {
			char *buf = sha1_to_hex(null_sha1);
			if (len < 37)
				strcpy(buf + len, "...");
			return buf;
		}
		else 
			return sha1_to_hex(sha1);
	}
	abblen = strlen(abbrev);
	if (abblen < 37) {
		static char hex[41];
		if (len < abblen && abblen <= len + 2)
			sprintf(hex, "%s%.*s", abbrev, len+3-abblen, "..");
		else
			sprintf(hex, "%s...", abbrev);
		return hex;
	}
	return sha1_to_hex(sha1);
}

			   int inter_name_termination,
			   struct diff_options *options)
	int abbrev = options->abbrev;
	const char *path_one, *path_two;
	int output_format = options->output_format;
	path_one = p->one->path;
	path_two = p->two->path;
		path_one = quote_one(path_one);
		path_two = quote_one(path_two);
	case DIFF_STATUS_COPIED:
	case DIFF_STATUS_RENAMED:
	case DIFF_STATUS_ADDED:
	case DIFF_STATUS_DELETED:
	if (output_format != DIFF_FORMAT_NAME_STATUS) {
		printf(":%06o %06o %s ",
		       p->one->mode, p->two->mode,
		       diff_unique_abbrev(p->one->sha1, abbrev));
		printf("%s ",
		       diff_unique_abbrev(p->two->sha1, abbrev));
	}
	printf("%s%c%s", status, inter_name_termination, path_one);
		printf("%c%s", inter_name_termination, path_two);
	if (path_one != p->one->path)
		free((void*)path_one);
	if (path_two != p->two->path)
		free((void*)path_two);
}

static void diff_flush_name(struct diff_filepair *p,
			    int inter_name_termination,
			    int line_termination)
{
	char *path = p->two->path;

	if (line_termination)
		path = quote_one(p->two->path);
	else
		path = p->two->path;
	printf("%s%c", path, line_termination);
	if (p->two->path != path)
		free(path);
static void diff_flush_patch(struct diff_filepair *p, struct diff_options *o)
	run_diff(p, o);
		x, one ? one : "",
		x, one ? one : "",
		p->score, p->status ? p->status : '?',
			p->status = DIFF_STATUS_UNMERGED;
			p->status = DIFF_STATUS_ADDED;
			p->status = DIFF_STATUS_DELETED;
			p->status = DIFF_STATUS_TYPE_CHANGED;
				p->status = DIFF_STATUS_COPIED;
			 * we are a copy.  Otherwise we are either a
			 * copy if the path stays, or a rename if it
			 * does not, but we already handled "stays" case.
				p->status = DIFF_STATUS_COPIED;
				p->status = DIFF_STATUS_RENAMED;
			p->status = DIFF_STATUS_MODIFIED;
			p->status = DIFF_STATUS_UNKNOWN;
void diff_flush(struct diff_options *options)
	int diff_output_format = options->output_format;
	int line_termination = options->line_termination;
	if (!line_termination)
		inter_name_termination = 0;
		if ((diff_output_format == DIFF_FORMAT_NO_OUTPUT) ||
		    (p->status == DIFF_STATUS_UNKNOWN))
		switch (diff_output_format) {
			diff_flush_patch(p, options);
		case DIFF_FORMAT_RAW:
		case DIFF_FORMAT_NAME_STATUS:
				       inter_name_termination,
				       options);
			break;
		case DIFF_FORMAT_NAME:
			diff_flush_name(p,
					inter_name_termination,
					line_termination);
	}
	if (strchr(filter, DIFF_STATUS_FILTER_AON)) {
			if (((p->status == DIFF_STATUS_MODIFIED) &&
			     ((p->score &&
			       strchr(filter, DIFF_STATUS_FILTER_BROKEN)) ||
			      (!p->score &&
			       strchr(filter, DIFF_STATUS_MODIFIED)))) ||
			    ((p->status != DIFF_STATUS_MODIFIED) &&
			     strchr(filter, p->status)))

			if (((p->status == DIFF_STATUS_MODIFIED) &&
			     ((p->score &&
			       strchr(filter, DIFF_STATUS_FILTER_BROKEN)) ||
			      (!p->score &&
			       strchr(filter, DIFF_STATUS_MODIFIED)))) ||
			    ((p->status != DIFF_STATUS_MODIFIED) &&
			     strchr(filter, p->status)))
void diffcore_std(struct diff_options *options)
	if (options->paths && options->paths[0])
		diffcore_pathspec(options->paths);
	if (options->break_opt != -1)
		diffcore_break(options->break_opt);
	if (options->detect_rename)
		diffcore_rename(options);
	if (options->break_opt != -1)
	if (options->pickaxe)
		diffcore_pickaxe(options->pickaxe, options->pickaxe_opts);
	if (options->orderfile)
		diffcore_order(options->orderfile);
	diffcore_apply_filter(options->filter);
void diffcore_std_no_resolve(struct diff_options *options)
	if (options->pickaxe)
		diffcore_pickaxe(options->pickaxe, options->pickaxe_opts);
	if (options->orderfile)
		diffcore_order(options->orderfile);
	diffcore_apply_filter(options->filter);
void diff_addremove(struct diff_options *options,
		    int addremove, unsigned mode,
	if (options->reverse_diff)
void diff_change(struct diff_options *options,
		 unsigned old_mode, unsigned new_mode,
	if (options->reverse_diff) {
void diff_unmerge(struct diff_options *options,
		  const char *path)