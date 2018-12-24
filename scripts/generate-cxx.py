import yaml
import jinja2
import argparse
import os
import sys

def render_template(template, data):
	env = jinja2.Environment(
		loader=jinja2.FileSystemLoader(["./", "/", ], followlinks=True), # relative first, then absolute.
		autoescape=jinja2.select_autoescape(['html', 'xml']),
		trim_blocks=True,
		keep_trailing_newline=True
	)
	return env.get_template(template).render(data=data)

def load_data(datadir):
	data = {}
	for dirname, subdirnames, filenames in os.walk(datadir):
		for filename in filenames:
			f = os.path.join(dirname, filename)
			e = os.path.splitext(filename)[0]
			data[e] = yaml.load(open(f, "r"))
	return data

def parse_args():
	parser = argparse.ArgumentParser(description="A Jinja template processor for C++")
	parser.add_argument("IN", help="input jinja template (required)")
	parser.add_argument("OUT", default="-", nargs="?", help="output filename (default stdout)")
	parser.add_argument("-d", "--datadir", help="directory containing yaml datafiles")
	return parser.parse_args()

def main():
	cfg = parse_args()
	data = load_data(cfg.datadir) if cfg.datadir else {}
	print(data)
	render = render_template(cfg.IN, data)
	if cfg.OUT == "-":
		sys.stdout.write(render)
	else:
		with open(cfg.OUT, "w") as outfile:
			outfile.write(render)

main()
