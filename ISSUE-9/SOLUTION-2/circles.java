
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;
import java.awt.image.BufferedImage;
import static java.lang.Math.*;
import java.util.Random;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;

/**
 * Olimex wpc #9
 *
 * Given 3+ points, determine if a circle fits them.
 *
 * Basic approach:
 *
 * 1. find a circle through any 3 points
 * 2. see if it fits all the rest.
 *
 * https://en.wikipedia.org/wiki/Circle
 * The key property:
 * The perpendicular bisector of a chord passes through the centre of a circle
 *
 * compile with:
 * javac circles.java
 * run with:
 * java circles
 *
 * @author notzed
 */
public class circles {

	static double epsilon = 0.00001;
	double[] points;
	Circle bestCircle;
	// details - this is just so it can be drawn
	Chord ca;
	Chord cb;
	Line pa;
	Line pb;
	Point cc;

	public circles(double... points) {
		this.points = points;

		if ((points.length % 1) != 0 || points.length < 6)
			throw new IllegalArgumentException("Need at least 3, pairs of points");
	}

	/**
	 * Analytical create a circle from 3 points in the set.
	 *
	 * @param a
	 * @param b
	 * @param c
	 * @return
	 */
	Circle createCircle(int a, int b, int c) {
		double ax = points[a * 2 + 0];
		double ay = points[a * 2 + 1];
		double bx = points[b * 2 + 0];
		double by = points[b * 2 + 1];
		double cx = points[c * 2 + 0];
		double cy = points[c * 2 + 1];

		// 
		ca = new Chord(ax, ay, bx, by);
		cb = new Chord(bx, by, cx, cy);

		pa = ca.bisector();
		pb = cb.bisector();

		//System.out.printf("Chord %s perp bisector %s\n", ca, pa);
		//System.out.printf("Chord %s perp bisector %s\n", cb, pb);

		cc = pa.intersect(pb);

		//System.out.printf("Centre: %s\n", cc);

		Circle C = cc == null ? null : new Circle(cc.x, cc.y, ax, ay);

		return C;
	}

	/**
	 * Use analytic solution
	 *
	 * It assumes the first 3 points are not coincident
	 */
	public boolean allOnCircle() {
		Circle c = createCircle(0, 1, 2);

		bestCircle = c;

		if (c != null) {
			for (int i = 0; i < points.length; i += 2) {
				if (!c.onCircle(points[i], points[i + 1]))
					return false;
			}
			return true;
		}
		return false;
	}

	static class Circle {

		double cx, cy, r;

		public Circle(double cx, double cy, double x1, double y1) {
			this.cx = cx;
			this.cy = cy;

			x1 -= cx;
			y1 -= cy;

			r = sqrt(x1 * x1 + y1 * y1);
		}

		public Circle(double x, double y, double r) {
			this.cx = x;
			this.cy = y;
			this.r = r;
		}

		public boolean onCircle(double x, double y) {
			return onCircle(x, y, epsilon);
		}

		public boolean onCircle(double x, double y, double e) {
			x -= cx;
			y -= cy;
			return abs(sqrt(x * x + y * y) - r) < e;
		}

		public String toString() {
			return String.format("%8.5f,%8.5f r %8.5f", cx, cy, r);
		}
	}

	static class Point {

		double x, y;

		public Point(double x, double y) {
			this.x = x;
			this.y = y;
		}

		public String toString() {
			return String.format("%8.5f,%8.5f", x, y);
		}
	}

	static class Line {

		double x0, y0, x1, y1;

		public Line(double x0, double y0, double x1, double y1) {
			this.x0 = x0;
			this.y0 = y0;
			this.x1 = x1;
			this.y1 = y1;
		}
		// https://en.wikipedia.org/wiki/Line-line_intersection

		public Point intersect(Line l) {
			double d = (x0 - x1) * (l.y0 - l.y1) - (y0 - y1) * (l.x0 - l.x1);

			// Parallel check
			if (abs(d) < epsilon)
				return null;

			double m0 = (x0 * y1 - y0 * x1);
			double m1 = (l.x0 * l.y1 - l.y0 * l.x1);

			double ix = m0 * (l.x0 - l.x1) - (x0 - x1) * m1;
			double iy = m0 * (l.y0 - l.y1) - (y0 - y1) * m1;

			return new Point(ix / d, iy / d);
		}

		public String toString() {
			return String.format("%8.5f,%8.5f,%8.5f,%8.5f", x0, y0, x1, y1);
		}
	}

	static class Chord extends Line {

		public Chord(double x0, double y0, double x1, double y1) {
			super(x0, y0, x1, y1);
		}

		public Line bisector() {
			// mid point
			double mx0 = (x1 + x0) / 2;
			double my0 = (y1 + y0) / 2;
			double mx1, my1;
			if (abs(y1 - y0) < epsilon) {
				// vertical perpendicular (untested path)
				mx1 = mx0;
				my1 = my0 + 10; // anything
			} else if (abs(x1 - x0) < epsilon) {
				// horizontal perpendicular (untested path)
				mx1 = mx0 + 10;
				my1 = my0;
			} else {
				// create perpendicular point
				mx1 = mx0 + (y1 - my0);
				my1 = my0 - (x1 - mx0);
			}

			return new Line(mx0, my0, mx1, my1);
		}
	}

	static void demo(String title, double... points) {
		circles c = new circles(points);

		c.open(title);

		StringBuilder sb = new StringBuilder("<html>");

		sb.append("<b>Points:</b> ").append(points.length / 2).append("<br>\n");

		sb.append("<b>Analytic:</b> ");
		if (c.allOnCircle()) {
			sb.append("All on circle<br>\n");
		} else {
			sb.append("No matching solution<br>\n");
		}
		if (c.bestCircle != null)
			c.showCircle(c.bestCircle);
		c.showPoints(c.points);
		System.out.println();

		c.label.setText(sb.toString());
		c.show();
	}
	JFrame jf;
	BufferedImage bi;
	JLabel label;
	Graphics2D gg;

	public void close() {
		gg.dispose();
		gg = null;
	}

	public void show() {
		jf.pack();

		jf.setVisible(true);
	}

	public void open(String title) {
		jf = new JFrame(title);
		bi = new BufferedImage(512, 512, BufferedImage.TYPE_INT_BGR);

		gg = bi.createGraphics();
		gg.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		gg.setPaint(Color.WHITE);

		// centre/mathematics scale
		gg.translate(256, 256);
		gg.scale(1, -1);
		
		jf.getContentPane().add(label = new JLabel(new ImageIcon(bi)));
		jf.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		label.setHorizontalTextPosition(JLabel.CENTER);
		label.setVerticalTextPosition(JLabel.BOTTOM);
	}

	public void showCircle(Circle C) {
		Graphics2D g = (Graphics2D) gg.create();

		g.setColor(Color.YELLOW);
		g.draw(new Line2D.Double(ca.x0, ca.y0, ca.x1, ca.y1));
		g.draw(new Line2D.Double(cb.x0, cb.y0, cb.x1, cb.y1));
		g.setColor(Color.BLUE);
		g.draw(new Line2D.Double(pa.x0, pa.y0, pa.x1, pa.y1));
		g.draw(new Line2D.Double(pb.x0, pb.y0, pb.x1, pb.y1));
		if (cc != null) {
			g.setPaint(Color.RED);
			g.fill(new Ellipse2D.Double(cc.x - 1, cc.y - 1, 3, 3));
			g.setColor(Color.RED);
			g.draw(new Ellipse2D.Double(C.cx - C.r, C.cy - C.r, C.r * 2, C.r * 2));
		}
		g.dispose();
	}

	public void showPoints(double[] p) {
		Ellipse2D.Double s = new Ellipse2D.Double();
		s.width = 3;
		s.height = 3;
		for (int i = 0; i < p.length; i += 2) {
			s.x = p[i] - 1.5;
			s.y = p[i + 1] - 1.5;
			gg.fill(s);
		}
	}

	public static void main(String[] args) {
		// Simple/obvious
		demo("Simple circle", -100, 0, 0, 100, 100, 0);

		// Good circle points
		int count = 300;
		Random rand = new Random();
		double[] p = new double[count * 2];
		// create a bunch of random points on a circle
		double cx = rand.nextDouble() * 100;
		double cy = rand.nextDouble() * 100;
		double r = rand.nextDouble() * 100 + 50;

		System.out.printf("Random circle at %f,%f r %f\n", cx, cy, r);
		for (int i = 0; i < count; i++) {
			double a = rand.nextDouble() * Math.PI * 2;

			double x = cx + cos(a) * r;
			double y = cy + sin(a) * r;

			p[i * 2 + 0] = x;
			p[i * 2 + 1] = y;
		}

		demo("Random points on good circle", p);

		// No longer on a circle
		p[0] += 100;
		demo("Not all on circle", p);
	}
}
