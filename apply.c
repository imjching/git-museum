#include <fnmatch.h>
#include "quote.h"
//  --numstat does numeric diffstat, and doesn't actually apply
//  --index-info shows the old and new index info for paths if available.
static const char *prefix;
static int prefix_length = -1;

static int allow_binary_replacement = 0;
static int numstat = 0;
static int no_add = 0;
static int show_index_info = 0;
static int line_termination = '\n';
static const char apply_usage[] =
"git-apply [--stat] [--numstat] [--summary] [--check] [--index] [--apply] [--no-add] [--index-info] [--allow-binary-replacement] [-z] <patch>...";
	int is_rename, is_copy, is_new, is_delete, is_binary;
	char old_sha1_prefix[41];
	char new_sha1_prefix[41];
		nr = xread(fd, buffer + size, nr);
		if (nr < 0)
	if (*line == '"') {
		/* Proposed "new-style" GNU patch/diff format; see
		 * http://marc.theaimsgroup.com/?l=git&m=112927316408690&w=2
		 */
		name = unquote_c_style(line, NULL);
		if (name) {
			char *cp = name;
			while (p_value) {
				cp = strchr(name, '/');
				if (!cp)
					break;
				cp++;
				p_value--;
			}
			if (cp) {
				/* name can later be freed, so we need
				 * to memmove, not just return cp
				 */
				memmove(name, cp, strlen(cp) + 1);
				free(def);
				return name;
			}
			else {
				free(name);
				name = NULL;
			}
		}
	}

		int len;
		const char *name;
		char *another;
		another = find_name(line, NULL, 1, 0);
		if (!another || memcmp(another, name, len))
			die("git-apply: bad git-diff - inconsistent %s filename on line %d", oldnew, linenr);
		free(another);
	else {
		/* expect "/dev/null" */
		if (memcmp("/dev/null", line, 9) || line[9] != '\n')
			die("git-apply: bad git-diff - expected /dev/null on line %d", linenr);
		return NULL;
	}
static int gitdiff_index(const char *line, struct patch *patch)
{
	/* index line is N hexadecimal, "..", N hexadecimal,
	 * and optional space with octal mode.
	 */
	const char *ptr, *eol;
	int len;

	ptr = strchr(line, '.');
	if (!ptr || ptr[1] != '.' || 40 < ptr - line)
		return 0;
	len = ptr - line;
	memcpy(patch->old_sha1_prefix, line, len);
	patch->old_sha1_prefix[len] = 0;

	line = ptr + 2;
	ptr = strchr(line, ' ');
	eol = strchr(line, '\n');

	if (!ptr || eol < ptr)
		ptr = eol;
	len = ptr - line;

	if (40 < len)
		return 0;
	memcpy(patch->new_sha1_prefix, line, len);
	patch->new_sha1_prefix[len] = 0;
	if (*ptr == ' ')
		patch->new_mode = patch->old_mode = strtoul(ptr+1, NULL, 8);
	return 0;
}

static const char *stop_at_slash(const char *line, int llen)
{
	int i;

	for (i = 0; i < llen; i++) {
		int ch = line[i];
		if (ch == '/')
			return line + i;
	}
	return NULL;
}

/* This is to extract the same name that appears on "diff --git"
 * line.  We do not find and return anything if it is a rename
 * patch, and it is OK because we will find the name elsewhere.
 * We need to reliably find name only when it is mode-change only,
 * creation or deletion of an empty file.  In any of these cases,
 * both sides are the same name under a/ and b/ respectively.
 */
static char *git_header_name(char *line, int llen)
	const char *name;
	const char *second = NULL;
	line += strlen("diff --git ");
	llen -= strlen("diff --git ");

	if (*line == '"') {
		const char *cp;
		char *first = unquote_c_style(line, &second);
		if (!first)

		/* advance to the first slash */
		cp = stop_at_slash(first, strlen(first));
		if (!cp || cp == first) {
			/* we do not accept absolute paths */
		free_first_and_fail:
			free(first);
			return NULL;
		}
		len = strlen(cp+1);
		memmove(first, cp+1, len+1); /* including NUL */

		/* second points at one past closing dq of name.
		 * find the second name.
		 */
		while ((second < line + llen) && isspace(*second))
			second++;

		if (line + llen <= second)
			goto free_first_and_fail;
		if (*second == '"') {
			char *sp = unquote_c_style(second, NULL);
			if (!sp)
				goto free_first_and_fail;
			cp = stop_at_slash(sp, strlen(sp));
			if (!cp || cp == sp) {
			free_both_and_fail:
				free(sp);
				goto free_first_and_fail;
			}
			/* They must match, otherwise ignore */
			if (strcmp(cp+1, first))
				goto free_both_and_fail;
			free(sp);
			return first;
		}

		/* unquoted second */
		cp = stop_at_slash(second, line + llen - second);
		if (!cp || cp == second)
			goto free_first_and_fail;
		cp++;
		if (line + llen - cp != len + 1 ||
		    memcmp(first, cp, len))
			goto free_first_and_fail;
		return first;
	/* unquoted first name */
	name = stop_at_slash(line, llen);
	if (!name || name == line)
	name++;

	/* since the first name is unquoted, a dq if exists must be
	 * the beginning of the second name.
	 */
	for (second = name; second < line + llen; second++) {
		if (*second == '"') {
			const char *cp = second;
			const char *np;
			char *sp = unquote_c_style(second, NULL);

			if (!sp)
				return NULL;
			np = stop_at_slash(sp, strlen(sp));
			if (!np || np == sp) {
			free_second_and_fail:
				free(sp);
				return NULL;
			}
			np++;
			len = strlen(np);
			if (len < cp - name &&
			    !strncmp(np, name, len) &&
			    isspace(name[len])) {
				/* Good */
				memmove(sp, np, len + 1);
				return sp;
			}
			goto free_second_and_fail;
		}
	}

			return NULL;
	patch->def_name = git_header_name(line, len);
			{ "index ", gitdiff_index },
			error("patch fragment without header at line %d: %.*s", linenr, (int)len-1, line);

                /* We allow "\ No newline at end of file". Depending
                 * on locale settings when the patch was produced we
                 * don't know what this line looks like. The only
                 * thing we do know is that it begins with "\ ".
		 * Checking for 12 is just for sanity check -- any
		 * l10n of "\ No newline..." is at least that long.
		 */
			if (len < 12 || memcmp(line, "\\ ", 2))
	/* If a fragment ends with an incomplete line, we failed to include
	 * it in the above loop because we hit oldlines == newlines == 0
	 * before seeing it.
	 */
	if (12 < size && !memcmp(line, "\\ ", 2))
		offset += linelen(line, size);

static inline int metadata_changes(struct patch *patch)
{
	return	patch->is_rename > 0 ||
		patch->is_copy > 0 ||
		patch->is_new > 0 ||
		patch->is_delete ||
		(patch->old_mode && patch->new_mode &&
		 patch->old_mode != patch->new_mode);
}

	if (!patchsize) {
		static const char *binhdr[] = {
			"Binary files ",
			"Files ",
			NULL,
		};
		int i;
		int hd = hdrsize + offset;
		unsigned long llen = linelen(buffer + hd, size - hd);

		if (!memcmp(" differ\n", buffer + hd + llen - 8, 8))
			for (i = 0; binhdr[i]; i++) {
				int len = strlen(binhdr[i]);
				if (len < size - hd &&
				    !memcmp(binhdr[i], buffer + hd, len)) {
					patch->is_binary = 1;
					break;
				}
			}

		/* Empty patch cannot be applied if:
		 * - it is a binary patch and we do not do binary_replace, or
		 * - text patch without metadata change
		 */
		if ((apply || check) &&
		    (patch->is_binary
		     ? !allow_binary_replacement
		     : !metadata_changes(patch)))
			die("patch with only garbage at line %d", linenr);
	}

	const char *prefix = "";
	char *qname = NULL;
	if (0 < (len = quote_c_style(name, NULL, NULL, 0))) {
		qname = xmalloc(len + 1);
		quote_c_style(name, qname, NULL, 0);
		name = qname;
	}

	if (len > max) {
		char *slash;
		prefix = "...";
		max -= 3;
		slash = strchr(name, '/');
		if (slash)
			name = slash;
	}
	if (patch->is_binary)
		printf(" %s%-*s |  Bin\n", prefix, len, name);
	else
		printf(" %s%-*s |%5d %.*s%.*s\n", prefix,
		       len, name, patch->lines_added + patch->lines_deleted,
		       add, pluses, del, minuses);
	if (qname)
		free(qname);
			int ret = xread(fd, buf + got, size - got);
			if (ret <= 0)
		if (len < size && patch[len] == '\\')
			if (*patch != '+' || !no_add) {
				memcpy(new + newsize, patch + 1, plen);
				newsize += plen;
			}
	const char *name = patch->old_name ? patch->old_name : patch->new_name;

	if (patch->is_binary) {
		unsigned char sha1[20];

		if (!allow_binary_replacement)
			return error("cannot apply binary patch to '%s' "
				     "without --allow-binary-replacement",
				     name);

		/* For safety, we require patch index line to contain
		 * full 40-byte textual SHA1 for old and new, at least for now.
		 */
		if (strlen(patch->old_sha1_prefix) != 40 ||
		    strlen(patch->new_sha1_prefix) != 40 ||
		    get_sha1_hex(patch->old_sha1_prefix, sha1) ||
		    get_sha1_hex(patch->new_sha1_prefix, sha1))
			return error("cannot apply binary patch to '%s' "
				     "without full index line", name);

		if (patch->old_name) {
			unsigned char hdr[50];
			int hdrlen;

			/* See if the old one matches what the patch
			 * applies to.
			 */
			write_sha1_file_prepare(desc->buffer, desc->size,
						"blob", sha1, hdr, &hdrlen);
			if (strcmp(sha1_to_hex(sha1), patch->old_sha1_prefix))
				return error("the patch applies to '%s' (%s), "
					     "which does not match the "
					     "current contents.",
					     name, sha1_to_hex(sha1));
		}
		else {
			/* Otherwise, the old one must be empty. */
			if (desc->size)
				return error("the patch applies to an empty "
					     "'%s' but it is not empty", name);
		}

		/* For now, we do not record post-image data in the patch,
		 * and require the object already present in the recipient's
		 * object database.
		 */
		if (desc->buffer) {
			free(desc->buffer);
			desc->alloc = desc->size = 0;
		}
		get_sha1_hex(patch->new_sha1_prefix, sha1);

		if (memcmp(sha1, null_sha1, 20)) {
			char type[10];
			unsigned long size;

			desc->buffer = read_sha1_file(sha1, type, &size);
			if (!desc->buffer)
				return error("the necessary postimage %s for "
					     "'%s' does not exist",
					     patch->new_sha1_prefix, name);
			desc->alloc = desc->size = size;
		}

		return 0;
	}
			return error("patch failed: %s:%ld",
				     name, frag->oldpos);
	const char *name = old_name ? old_name : new_name;
		int stat_ret = lstat(old_name, &st);
				return error("%s: does not exist in index",
					     old_name);
			if (stat_ret < 0) {
				struct checkout costate;
				if (errno != ENOENT)
					return error("%s: %s", old_name,
						     strerror(errno));
				/* checkout */
				costate.base_dir = "";
				costate.base_dir_len = 0;
				costate.force = 0;
				costate.quiet = 0;
				costate.not_new = 0;
				costate.refresh_cache = 1;
				if (checkout_entry(active_cache[pos],
						   &costate) ||
				    lstat(old_name, &st))
					return -1;
			}

				return error("%s: does not match index",
					     old_name);
		else if (stat_ret < 0)
			return error("%s: %s", old_name, strerror(errno));

		if (!patch->new_mode) {
			if (patch->is_new)
				patch->new_mode = S_IFREG | 0644;
			else
				patch->new_mode = patch->old_mode;
		}
		return error("%s: patch does not apply", name);
static inline int is_null_sha1(const unsigned char *sha1)
	return !memcmp(sha1, null_sha1, 20);
static void show_index_list(struct patch *list)
	struct patch *patch;

	/* Once we start supporting the reverse patch, it may be
	 * worth showing the new sha1 prefix, but until then...
	 */
	for (patch = list; patch; patch = patch->next) {
		const unsigned char *sha1_ptr;
		unsigned char sha1[20];
		const char *name;

		name = patch->old_name ? patch->old_name : patch->new_name;
		if (patch->is_new)
			sha1_ptr = null_sha1;
		else if (get_sha1(patch->old_sha1_prefix, sha1))
			die("sha1 information is lacking or useless (%s).",
			    name);
		else
			sha1_ptr = sha1;

		printf("%06o %s	",patch->old_mode, sha1_to_hex(sha1_ptr));
		if (line_termination && quote_c_style(name, NULL, NULL, 0))
			quote_c_style(name, NULL, stdout, 0);
		else
			fputs(name, stdout);
		putchar(line_termination);
static void numstat_patch_list(struct patch *patch)
{
	for ( ; patch; patch = patch->next) {
		const char *name;
		name = patch->old_name ? patch->old_name : patch->new_name;
		printf("%d\t%d\t", patch->lines_added, patch->lines_deleted);
		if (line_termination && quote_c_style(name, NULL, NULL, 0))
			quote_c_style(name, NULL, stdout, 0);
		else
			fputs(name, stdout);
		putchar('\n');
	}
}

		       (int)(old - p->old_name), p->old_name,
		int len = quote_c_style(patch->old_name, NULL, NULL, 0);
		if (!len)
			len = strlen(patch->old_name);
		int len = quote_c_style(patch->new_name, NULL, NULL, 0);
		if (!len)
			len = strlen(patch->new_name);
static int try_create_file(const char *path, unsigned int mode, const char *buf, unsigned long size)
{
	int fd;

	if (S_ISLNK(mode))
		return symlink(buf, path);
	fd = open(path, O_CREAT | O_EXCL | O_WRONLY | O_TRUNC, (mode & 0100) ? 0777 : 0666);
	if (fd < 0)
		return -1;
	while (size) {
		int written = xwrite(fd, buf, size);
		if (written < 0)
			die("writing file %s: %s", path, strerror(errno));
		if (!written)
			die("out of space writing file %s", path);
		buf += written;
		size -= written;
	}
	if (close(fd) < 0)
		die("closing file %s: %s", path, strerror(errno));
	return 0;
}

static void create_one_file(const char *path, unsigned mode, const char *buf, unsigned long size)
	if (!try_create_file(path, mode, buf, size))
		return;
	if (errno == ENOENT) {
		if (!try_create_file(path, mode, buf, size))
			return;
	if (errno == EEXIST) {
		unsigned int nr = getpid();
		for (;;) {
			const char *newpath;
			newpath = mkpath("%s~%u", path, nr);
			if (!try_create_file(newpath, mode, buf, size)) {
				if (!rename(newpath, path))
					return;
				unlink(newpath);
				break;
			}
			if (errno != EEXIST)
				break;
		}			
	die("unable to write file %s mode %o", path, mode);
	create_one_file(path, mode, buf, size);	
	add_index_file(path, mode, buf, size);
static void write_out_results(struct patch *list, int skipped_patch)
	if (!list && !skipped_patch)
static struct excludes {
	struct excludes *next;
	const char *path;
} *excludes;

static int use_patch(struct patch *p)
{
	const char *pathname = p->new_name ? p->new_name : p->old_name;
	struct excludes *x = excludes;
	while (x) {
		if (fnmatch(x->path, pathname, 0) == 0)
			return 0;
		x = x->next;
	}
	if (0 < prefix_length) {
		int pathlen = strlen(pathname);
		if (pathlen <= prefix_length ||
		    memcmp(prefix, pathname, prefix_length))
			return 0;
	}
	return 1;
}

	int skipped_patch = 0;
		if (use_patch(patch)) {
			patch_stats(patch);
			*listp = patch;
			listp = &patch->next;
		} else {
			/* perhaps free it a bit better? */
			free(patch);
			skipped_patch++;
		}
		write_out_results(list, skipped_patch);
	if (show_index_info)
		show_index_list(list);
	if (numstat)
		numstat_patch_list(list);

		if (!strncmp(arg, "--exclude=", 10)) {
			struct excludes *x = xmalloc(sizeof(*x));
			x->path = arg + 10;
			x->next = excludes;
			excludes = x;
			continue;
		}
		if (!strcmp(arg, "--no-add")) {
			no_add = 1;
		if (!strcmp(arg, "--allow-binary-replacement")) {
			allow_binary_replacement = 1;
			continue;
		}
		if (!strcmp(arg, "--numstat")) {
			apply = 0;
			numstat = 1;
			continue;
		}
		if (!strcmp(arg, "--index-info")) {
			apply = 0;
			show_index_info = 1;
		if (!strcmp(arg, "-z")) {
			line_termination = 0;
			continue;
		}

		if (check_index && prefix_length < 0) {
			prefix = setup_git_directory();
			prefix_length = prefix ? strlen(prefix) : 0;
			git_config(git_default_config);
		}
		if (0 < prefix_length)
			arg = prefix_filename(prefix, prefix_length, arg);
